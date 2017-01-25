#ifndef CONNECTION_H
#define CONNECTION_H

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include <string>

namespace http {
namespace server {

class connection
  : public std::enable_shared_from_this<connection>
{
public:
  connection(const connection&) = delete;
  connection& operator=(const connection&) = delete;

  explicit connection(boost::asio::ip::tcp::socket socket);

  void start();

  void stop();

private:
<<<<<<< HEAD
  void do_read_and_write();

  //void do_write();
=======
  void do_read();

  void do_write();
>>>>>>> master

  boost::asio::ip::tcp::socket socket_;

  std::array<char, 8192> buffer_;

  std::string reply_;
};

typedef std::shared_ptr<connection> connection_ptr;

} // namespace server
} // namespace http

#endif // HTTP_CONNECTION_HPP