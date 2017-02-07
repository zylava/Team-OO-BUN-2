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


// void connection::do_read()
// {
//   auto self(shared_from_this());
//   socket_.async_read_some(boost::asio::buffer(buffer_),
//       [this, self](boost::system::error_code ec, std::size_t bytes_transferred)
//       {
//         if (!ec)
//         {
//           // Appends the bytes read by async_read_some to the 'reply_' string
//           reply_.append(buffer_.data(), bytes_transferred);
//           if (reply_.substr(reply_.size() - 4, 4) == "\r\n\r\n")
//           {
//             // HTTP response and content type
//             // Send back a 200 (OK) code and plain text type
//             const char* response_string = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";

//             // We will be using 'response' to hold the request data from the user
//             std::string response;
//             response.append(reply_);

//             // Cast the string into a char* as boost::asio::write requires a char*
//             // and the length of what char* points to (we use strlen for this)
//             const char* reply_body = response.c_str();
            
//             write_response(response_string, reply_body); 
//           }
//           else
//           {
//             connectionStatus = -1; 
//             stop(); 
//           }
//         }
//       });
// }

const char* connection::get_response()
{
  return response_header;
}

const char* connection::get_reply()
{
  return reply_body.c_str();
}

void connection::do_read()
{
  auto self(shared_from_this());
  socket_.async_read_some(boost::asio::buffer(buffer_),
      [this, self](boost::system::error_code ec, std::size_t bytes_transferred)
      {
        if (!ec)
        {
          //  echoing 
          // rep.content.append(buffer_.data(), bytes_transferred);
          // rep.header_name = "HTTP/1.1 200 OK"; 
          // rep.header_value = "Content-Type: text/plain";
          // rep.status = reply::ok; 

          //static 
          request_parser::result_type result;
          std::tie(result, std::ignore) = request_parser_.parse(
          req, buffer_.data(), buffer_.data() + bytes_transferred);

          std::string server_mode="";
          std::size_t first_slash_pos = req.uri.find_first_of("/"); 
          for(char& c : req.uri.substr(first_slash_pos + 1)) {
            if (c == '/'){
              break; 
            } 
            server_mode += c;
          }

          //std::cout << server_mode << std::endl;

          if (result == request_parser::good && server_mode == "echo"){
            rep.content.append(buffer_.data(), bytes_transferred);
            rep.headers.resize(2);
            rep.headers[0].name = "Content-Length";
            rep.headers[0].value = std::to_string(rep.content.size());
            rep.headers[1].name = "Content-Type";
            rep.headers[1].value = "text/plain";
            rep.status = reply::ok;
            write_response();

          }
          else if (result == request_parser::good)
          {
            request_handler_.handle_request(req, rep);
            write_response(); 
          }
          else {
            //TODO: Bad request
          }

        }
      });
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