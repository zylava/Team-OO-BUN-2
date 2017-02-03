#include "server.hpp"
#include <signal.h>
#include <utility>
#include <string>
#include <iostream>
#include <boost/bind.hpp>

namespace http {
namespace server {
    //Constructor
    server::server(const std::string& address, const std::string& port, const std::string& doc_root)
      : io_service_(), signals_(io_service_), acceptor_(io_service_), socket_(io_service_)
    {
      boost::asio::ip::tcp::resolver resolver(io_service_);
      boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve({address, port});
      acceptor_.open(endpoint.protocol());
      acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
      acceptor_.bind(endpoint);
      acceptor_.listen();

      portNum_ = port;
      address_ = address;
      fileName_ = doc_root; 

      // signals_.add(SIGINT);
      // signals_.add(SIGTERM);
      // #if defined(SIGQUIT)
      // signals_.add(SIGQUIT);
      // #endif // defined(SIGQUIT)

      //do_await_stop();

      do_accept();
    }

    void server::run()
    {
      isRunning = true; 
      io_service_.run();
    }

    void server::do_accept()
    {
      acceptor_.async_accept(socket_, boost::bind(&server::create_connection, this, _1));
    }

    bool server::create_connection(const boost::system::error_code& ec) 
    {
      // Error check, if the website name given is not valid then this will return
      if (!acceptor_.is_open()) 
      {
        return false;
      }

      if (ec) 
      {
        return false;
      }
      else // If no detected problems with creating then start the connection
      {
        // For testing 
        isRunning = true;
        
        // Creates a shared connection ptr and calls start on it
        // std::move gets rid of the copy constructor delete error
        std::make_shared<connection>(std::move(socket_))->start();
      }
      
      do_accept();
      return true;
    }

    bool server::getStatus() 
    {
      return isRunning; 
    }

    std::string server::getPortNum()
    {
      return portNum_; 
    }

    std::string server::getAddress()
    {
      return address_;
    }

    std::string server::getFileName()
    {
      return fileName_;
    }

    void server::do_await_stop()
    {
      signals_.async_wait(
      [this](boost::system::error_code /*ec*/, int /*signo*/)
      {
        // The server is stopped by cancelling all outstanding asynchronous
        // operations. Once all operations have finished the io_service::run()
        // call will exit.
        std::cout << " \n";
        acceptor_.close();
        io_service_.stop();
      });
    }

  }
} 