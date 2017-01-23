#ifndef ECHO_SERVER_H
#define ECHO_SERVER_H

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

  explicit connection(boost::asio::ip::tcp::socket socket,
      connection_manager& manager, request_handler& handler);

  /// Start the first asynchronous operation for the connection.
  void start();

  /// Stop all asynchronous operations associated with the connection.
  void stop();

private:
  /// Perform an asynchronous read operation.
  void do_read();

  /// Perform an asynchronous write operation.
  void do_write();

  /// Socket for the connection.
  boost::asio::ip::tcp::socket socket_;

  /// Buffer for incoming data.
  std::array<char, 8192> buffer_;

  /// The reply to be sent back to the client.
  std::string reply_;
};

typedef std::shared_ptr<connection> connection_ptr;

} // namespace server
} // namespace http

#endif // HTTP_CONNECTION_HPP