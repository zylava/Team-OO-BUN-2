#include "connection.h"
#include <utility>
#include <vector>
#include <iostream> 
#include "request_handler.h"
#include <boost/asio.hpp>

namespace http {
namespace server {

connection::connection(boost::asio::ip::tcp::socket socket, std::map <std::string, RequestHandler*> handlers)
  : socket_(std::move(socket)), handlers_(handlers)
{
}

void connection::start()
{
  do_read();
}

void connection::stop()
{
  socket_.close();
  io_service_.stop();
}

Response connection::get_reply()
{
  return rep;
}

void connection::do_read()
{
  auto self(shared_from_this());
  socket_.async_read_some(boost::asio::buffer(buffer_),
      [this, self](boost::system::error_code ec, std::size_t bytes_transferred)
      {
        if (!ec)
        {
          // Turn the request buffer into a string
          std::string s = "";
          s.append(buffer_.data(), buffer_.data() + bytes_transferred);

          // Parse the request
          std::unique_ptr<Request> request = Request::Parse(s); 

          req = *request;

          // Determine the file handler needed
          RequestHandler* server_mode = parse_command(req);

          // Check if the parser returned null
          if (server_mode != nullptr) {
            // Check if the request handler returned not found
            if (server_mode->HandleRequest(req, &rep) == RequestHandler::Status::NOT_FOUND){
              // Call the default/not found handler
              handlers_["default"]->HandleRequest(req, &rep);
            }
            // Write back to the client
            write_response();
          }
        }
      });
}

// Determines which handler the input uri should use
RequestHandler* connection::parse_command(Request& req)
{
	std::string mode = req.uri();

  // Go backward from the end of the uri
  for (int index = mode.length(); index > 0; index--) {
    // Update the size of the uri string 
    mode.resize(index);

    // Find longest matching path in the handlers
    if (handlers_.find(mode) != handlers_.end()) {
      // Found: return pointer to the handler
      RequestHandler* handler = handlers_[mode];
      return handler;
    }
  }
  // No matching handler found, return nullptr
  return nullptr;
}

// Write response to the client
void connection::write_response()
{
  auto self(shared_from_this());
  boost::asio::async_write(socket_, boost::asio::buffer(rep.ToString()),
      [this, self](boost::system::error_code ec, std::size_t)
      {
        if (!ec)
        {
          // Initiate graceful connection closure.
          boost::system::error_code ignored_ec;
          socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
            ignored_ec);
        }

      });

}

} // namespace server
} // namespace http