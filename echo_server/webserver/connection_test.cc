#include "gtest/gtest.h"
#include "connection.hpp"
#include "gmock/gmock.h"
#include <boost/asio.hpp>
//#include "mock_connection.h"

TEST(ConnectionTest, SimpleTest) {

  boost::asio::io_service io_service_;
  boost::asio::ip::tcp::socket socket_(io_service_);
  socket_.open(boost::asio::ip::tcp::v4());

  const char* response_string = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
  const char* reply_string = "GET index.html"; 

  std::make_shared<http::server::connection>(std::move(socket_))-> start();
  std::make_shared<http::server::connection>(std::move(socket_))-> write_response(response_string, reply_string);

  EXPECT_EQ(1,  std::make_shared<http::server::connection>(std::move(socket_))-> getServerStatus());	

  //http::server::connection con(socket_);
  // con.start();
  // http::server::connection start(); 



  // con.write_response(response_string, reply_string);
  //http::server::connection write_response(response_string, reply_string); 
 
}
