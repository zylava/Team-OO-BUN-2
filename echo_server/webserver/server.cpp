#include "server.hpp"
#include <signal.h>
#include <utility>

namespace http {
namespace server {

server::server(const std::string& address, const std::string& port,
    const std::string& doc_root)
  : io_service_(),
    signals_(io_service_),
    acceptor_(io_service_),
    socket_(io_service_)
{

<<<<<<< HEAD
  // do_await_stop();
=======
  do_await_stop();
>>>>>>> master

  boost::asio::ip::tcp::resolver resolver(io_service_);
  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve({address, port});
  acceptor_.open(endpoint.protocol());
  acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  acceptor_.bind(endpoint);
  acceptor_.listen();

  do_accept();
}

void server::run()
{
  io_service_.run();
}

void server::do_accept()
{
  acceptor_.async_accept(socket_,
      [this](boost::system::error_code ec)
      {
        if (!acceptor_.is_open())
        {
          return;
        }

<<<<<<< HEAD
        if (!ec)
        {
          // Creates a shared connection ptr and calls start on it
          std::make_shared<connection>(std::move(socket_))->start();
        }

=======
>>>>>>> master
        do_accept();
      });
}

<<<<<<< HEAD
// void server::do_await_stop()
// {
//   signals_.async_wait(
//       [this](boost::system::error_code /*ec*/, int /*signo*/)
//       {
//         acceptor_.close();
//       });
// }
=======
void server::do_await_stop()
{
  signals_.async_wait(
      [this](boost::system::error_code /*ec*/, int /*signo*/)
      {
        acceptor_.close();
      });
}
>>>>>>> master

} // namespace server
} // namespace http