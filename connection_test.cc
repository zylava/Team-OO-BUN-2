#include "gtest/gtest.h"
#include "connection.hpp"
#include "gmock/gmock.h"
#include <boost/asio.hpp>
#include "server.hpp"


TEST(ConnectionTest, StatusTest) {
  boost::asio::io_service io_service_;
  boost::asio::ip::tcp::socket socket_(io_service_);

  socket_.open(boost::asio::ip::tcp::v4());

  auto my_connection = std::make_shared<http::server::connection>(std::move(socket_));
  my_connection->start(); 

  EXPECT_EQ(1, my_connection->getConnectionStatus()); 
}

TEST(ConnectionTest, ResponseHeaderTest) {

  boost::asio::io_service io_service_;
  boost::asio::ip::tcp::socket socket_(io_service_);

  const char* response_string = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";

  std::string request = "GET /index.html HTTP/1.1";

  std::shared_ptr<http::server::connection> con = std::make_shared<http::server::connection>(std::move(socket_));
  con->construct_response(request);

  const char* response = con->get_response();

  EXPECT_EQ(*response_string, *response);
  EXPECT_EQ(strlen(response_string), strlen(response)); 
}

TEST(ConnectionTest, ReplyBodyTest) {

  boost::asio::io_service io_service_;
  boost::asio::ip::tcp::socket socket_(io_service_);

  std::string request = "GET /index.html HTTP/1.1\r\nHost: localhost:1080";

  auto con = std::make_shared<http::server::connection>(std::move(socket_));
  con->construct_response(request);

  const char* response = con->get_reply();
  const char* response_string = request.c_str();
  
  EXPECT_EQ(*response_string, *(response));  
  EXPECT_EQ(strlen(response_string), strlen(response));
}
