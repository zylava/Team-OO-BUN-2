#ifndef CONNECTION_H
#define CONNECTION_H

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include <string>
#include "reply.h"
#include "request.hpp"
#include "request_handler.h"

namespace http {
namespace server {

class connection : public std::enable_shared_from_this<connection>
{
public:
  // Does not allow us to make copies of this class
  // connection(const connection&) = delete;
  // connection& operator=(const connection&) = delete;

  explicit connection(boost::asio::ip::tcp::socket socket, request_handler& handler);

  void start();
  
  void stop();

  const char* get_response();

  const char* get_reply();
  
  int getConnectionStatus(); 

  void construct_response(std::string reply);
  
  void write_response();
  
private:
  void do_read();

  boost::asio::io_service io_service_;

  boost::asio::ip::tcp::socket socket_;

  std::array<char, 8192> buffer_;

  std::string reply_;

  const char* response_header;

  std::string reply_body;

  reply rep; 

  request req; 

  int connectionStatus; // 1 success 0 unsuccessful -1 error

  /// The handler used to process the incoming request.
  request_handler& request_handler_;
};

typedef std::shared_ptr<connection> connection_ptr;

} // namespace server
} // namespace http

#endif // HTTP_CONNECTION_HPP