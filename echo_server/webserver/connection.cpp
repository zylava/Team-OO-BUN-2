#include "connection.hpp"
#include <utility>
#include <vector>
<<<<<<< HEAD
#include <iostream> 
=======
>>>>>>> master

namespace http {
namespace server {

connection::connection(boost::asio::ip::tcp::socket socket)
  : socket_(std::move(socket))
{
}

void connection::start()
{
<<<<<<< HEAD
  do_read_and_write();
=======
  do_read();
>>>>>>> master
}

void connection::stop()
{
  socket_.close();
}

<<<<<<< HEAD
void connection::do_read_and_write()
=======
void connection::do_read()
>>>>>>> master
{
  auto self(shared_from_this());
  socket_.async_read_some(boost::asio::buffer(buffer_),
      [this, self](boost::system::error_code ec, std::size_t bytes_transferred)
      {
        if (!ec)
        {
<<<<<<< HEAD
          // HTTP OK response
          const std::string okay_reponse = "HTTP/1.1 200 OK\r\n";
          // Content type string
          const std::string content_type = "Content-Type: text/plain\r\n";

          // We will be using 'response' to hold the input, a vector of type
          // const_buffer since async_write requires a type buffer 
          std::vector<boost::asio::const_buffer> response;

          response.push_back(boost::asio::buffer(okay_reponse));
          response.push_back(boost::asio::buffer(content_type));

          // Appends the bytes read by async_read_some to the 'reply_' string
        	reply_.append(buffer_.data(), bytes_transferred);

          response.push_back(boost::asio::buffer(reply_));

          std::cout << reply_ << std::endl;

          for(unsigned int i = 0; i < response.size(); i++){
            socket_.send(boost::asio::buffer(response[i])); 
          }
          // boost::asio:async_write requites a const ConstBufferSequence as the second argument
          boost::asio::async_write(socket_, response,
              [this, self](boost::system::error_code ec, std::size_t)
              {
                if (!ec) {
                  // Initiate graceful connection closure.
                  boost::system::error_code ignored_ec;
                  socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
                    ignored_ec);
                }
              });
=======
        	// reply_.append(buffer_.data(), bytes_transferred);
>>>>>>> master
        }
      });
}

<<<<<<< HEAD
=======
void connection::do_write()
{
  auto self(shared_from_this());
  // boost::asio::async_write(socket_, reply_.to_buffers(),
  //     [this, self](boost::system::error_code ec, std::size_t)
  //     {
  //       if (!ec)
  //       {
  //         // Initiate graceful connection closure.
  //         boost::system::error_code ignored_ec;
  //         socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
  //           ignored_ec);
  //       }
        
  //     });
}
>>>>>>> master

} // namespace server
} // namespace http