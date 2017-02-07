#include "gtest/gtest.h"
#include "connection.hpp"
#include "gmock/gmock.h"
#include <boost/asio.hpp>
#include "request.hpp"
#include "request_handler.h"
#include "request_parser.hpp"

TEST(ConnectionTest, ServerModeTest)
{
  boost::asio::io_service io_service_;
  boost::asio::ip::tcp::socket socket_(io_service_);
  std::string doc_root = ".";
  http::server::request_handler handler(doc_root);

  http::server::request_parser request_parser_;
  http::server::request_parser::result_type result;
  http::server::request request_;

  auto my_connection = std::make_shared<http::server::connection>(std::move(socket_), handler);
  std::string input_request = "GET /echo HTTP/1.1\r\n\r\n";

  std::tie(result, std::ignore) = request_parser_.parse(
          request_, input_request.begin(), input_request.end());

  std::string mode = my_connection->parse_command(request_);

  EXPECT_EQ(mode, "echo");

}

TEST(ConnectionTest, ConstructEchoResponseTest)
{
  boost::asio::io_service io_service_;
  boost::asio::ip::tcp::socket socket_(io_service_);
  std::string doc_root = ".";
  http::server::request_handler handler(doc_root);

  http::server::request request_;

  auto my_connection = std::make_shared<http::server::connection>(std::move(socket_), handler);
  std::string input_request = "GET /echo HTTP/1.1\r\n"
                "Host: localhost:1080\r\n"
                "User-Agent: Mozilla/5.0\r\n"
                "Accept: text/html\r\n\r\n";

  my_connection->create_echo_response(input_request.c_str(), input_request.length());
  
  EXPECT_EQ(my_connection->get_reply().status, 200);
  EXPECT_EQ(my_connection->get_reply().content, input_request);
  EXPECT_EQ(my_connection->get_reply().headers[1].name, "Content-Type");
  EXPECT_EQ(my_connection->get_reply().headers[1].value, "text/plain");

}

TEST(ConnectionTest, StatusTest) {
  boost::asio::io_service io_service_;
  boost::asio::ip::tcp::socket socket_(io_service_);

  socket_.open(boost::asio::ip::tcp::v4());

  std::string doc_root = ".";
  http::server::request_handler handler(doc_root);
  auto my_connection = std::make_shared<http::server::connection>(std::move(socket_), handler);
  my_connection->start(); 

  EXPECT_EQ(1, my_connection->getConnectionStatus()); 
}