#ifndef ECHO_SERVER_H
#define ECHO_SERVER_H

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include <string>
#include "reply.hpp"

namespace http {
namespace server {

class connection
  : public std::enable_shared_from_this<connection>
{
public:
  connection(const connection&) = delete;
  connection& operator=(const connection&) = delete;

  void start();

  void stop();
  explicit connection(boost::asio::ip::tcp::socket socket);

private:
  void do_read();

  void do_write();

  boost::asio::ip::tcp::socket socket_;

  std::array<char, 8192> buffer_;

  reply reply_;
};

typedef std::shared_ptr<connection> connection_ptr;

} // namespace server
} // namespace http

#endif // HTTP_CONNECTION_HPP