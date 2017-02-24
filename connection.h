#ifndef CONNECTION_H
#define CONNECTION_H

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include <string>
#include "request_handler.h"
#include <map>

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

  explicit connection(boost::asio::ip::tcp::socket socket, std::map <std::string, RequestHandler*> handlers);

  void start();
  
  void stop();

  Response get_response();

  void write_response();

  Request call_parser(std::string data);

  RequestHandler* find_handler(Request& request);

  RequestHandler::Status call_handler(RequestHandler* handler_mode);
  
private:
  void do_read();

  boost::asio::io_service io_service_;

  boost::asio::ip::tcp::socket socket_;

  std::array<char, MAX_BUFFER_SIZE> buffer_;

  Response res; 

  Request req; 

  /// The handler used to process the incoming request.
  std::map <std::string, RequestHandler*> handlers_;

};

} // namespace server
} // namespace http

#endif // HTTP_CONNECTION_HPP