#ifndef CONNECTION_H
#define CONNECTION_H

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include <string>
#include "reply.h"
#include "request.hpp"
#include "request_handler.h"
#include "request_parser.hpp"

namespace http {
namespace server {

// 8192 is maximum size of a package sent on a network
static const int MAX_BUFFER_SIZE = 8192;

class connection : public std::enable_shared_from_this<connection>
{
public:
  // Does not allow us to make copies of this class
  // connection(const connection&) = delete;
  // connection& operator=(const connection&) = delete;

  explicit connection(boost::asio::ip::tcp::socket socket, request_handler& handler);

  void start();
  
  void stop();

  reply get_reply();
  
  int getConnectionStatus(); 
  
  void write_response();

  std::string parse_command(request request);

  void create_echo_response(const char* data, std::size_t bytes);
  
private:
  void do_read();

  boost::asio::io_service io_service_;

  boost::asio::ip::tcp::socket socket_;

  std::array<char, MAX_BUFFER_SIZE> buffer_;

  reply rep; 

  request req; 

  enum connection_status
  {
    error = -1, 
    unsuccessful = 0, 
    success = 1
  };

  int connectionStatus;

  /// The handler used to process the incoming request.
  request_handler& request_handler_;

  request_parser request_parser_;

};

typedef std::shared_ptr<connection> connection_ptr;

} // namespace server
} // namespace http

#endif // HTTP_CONNECTION_HPP