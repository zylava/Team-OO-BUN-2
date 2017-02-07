#include "connection.hpp"
#include <utility>
#include <vector>
#include <iostream> 
#include "request_handler.h"

namespace http {
namespace server {

connection::connection(boost::asio::ip::tcp::socket socket, request_handler& handler)
  : socket_(std::move(socket)), request_handler_(handler)
{
}

void connection::start()
{
  connectionStatus = 1; // success
  do_read();
}

void connection::stop()
{
  socket_.close();
  io_service_.stop();
}

int connection::getConnectionStatus()
{
  return connectionStatus; 
}

reply connection::get_reply()
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
          request_parser::result_type result;
          std::tie(result, std::ignore) = request_parser_.parse(
          	req, buffer_.data(), buffer_.data() + bytes_transferred);

          // Determine /echo or /static
          std::string server_mode = parse_command(req);

          // echo
          if (result == request_parser::good && server_mode == "echo"){
          	create_echo_response(buffer_.data(), bytes_transferred);
            write_response();

          } // static 
          else if (result == request_parser::good)
          {
            request_handler_.handle_request(req, rep);
            write_response(); 
          }
        }
      });
}

// Determines whether the input URL is /echo or /static
std::string connection::parse_command(request req)
{
	std::string mode;
	std::size_t first_slash_pos = req.uri.find_first_of("/"); 
	for(char& c : req.uri.substr(first_slash_pos + 1)) {
		if (c == '/'){
		 	break; 
		} 
		mode += c;
	}
	return mode;
}

// Reads in the buffer_ data and constructs a reply with the proper echo headers and body
void connection::create_echo_response(const char* data, std::size_t bytes_transferred)
{
	rep.content.append(data, bytes_transferred);
    rep.headers.resize(2);
    rep.headers[0].name = "Content-Length";
    rep.headers[0].value = std::to_string(rep.content.size());
    rep.headers[1].name = "Content-Type";
    rep.headers[1].value = "text/plain";
    rep.status = reply::ok;	
}

void connection::write_response()
{
  auto self(shared_from_this());
  boost::asio::async_write(socket_, rep.to_buffers(),
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