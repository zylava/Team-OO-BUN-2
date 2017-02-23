#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include <string>
#include "connection.h"
#include "request_handler.h"
#include <map> 

namespace http {
namespace server {
    class server
    {
    public:
      // Does not allow us to make copies of the server
      // server(const server&) = delete;
      // server& operator=(const server&) = delete;

      explicit server(const std::string& address, NginxConfig config);

      void run(); 
      bool getStatus(); 
      void do_await_stop();
      //bool create_connection(const boost::system::error_code& ec);
      std::string getPortNum(); 
      std::string getAddress();  

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

      /// The handlers for all incoming requests.
      std::map <std::string, RequestHandler*> handlers;

    };
    
} // namespace server
} // namespace http

#endif