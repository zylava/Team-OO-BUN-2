#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include <string>
#include "connection.hpp"
#include "request_handler.h"

namespace http {
namespace server {
    class server
    {
    public:
      // Does not allow us to make copies of the server
      // server(const server&) = delete;
      // server& operator=(const server&) = delete;

      explicit server(const std::string& address, const std::string& port, const std::string& doc_root);

      void run(); 
      bool getStatus(); 
      void stop();
      std::string getPortNum(); 
      std::string getAddress(); 
      std::string getFileName(); 
      void do_await_stop(); 

    private:
      void do_accept();
      
      boost::asio::io_service io_service_;

      boost::asio::signal_set signals_;

      boost::asio::ip::tcp::acceptor acceptor_;

      boost::asio::ip::tcp::socket socket_;

      bool isRunning = false;

      std::string portNum_; 
      std::string address_; 
      std::string fileName_;

      /// The handler for all incoming requests.
      request_handler request_handler_;

    };
  }
} 

#endif