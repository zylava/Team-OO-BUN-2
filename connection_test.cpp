#include "gtest/gtest.h"
#include "connection.h"
#include "gmock/gmock.h"
#include <boost/asio.hpp>
#include "request_handler.h"

namespace http {
namespace server {

TEST(ConnectionTest, FindEchoHandlerTest)
{
  boost::asio::io_service io_service_;
  boost::asio::ip::tcp::socket socket_(io_service_);
  
  std::map <std::string, RequestHandler*> handlers;
  NginxConfig echo_config;

  handlers["/echo"] = RequestHandler::CreateByName("EchoHandler");
  handlers["/echo"]->Init("", echo_config);

  auto my_connection = std::make_shared<http::server::connection>(std::move(socket_), handlers);
  
  std::string raw_request = "GET /echo HTTP/1.1\r\n\r\n";
  auto request = Request::Parse(raw_request); 
  Request req = *request;

  RequestHandler* handler = my_connection->find_handler(req);

  EXPECT_EQ(handlers["/echo"], handler);
}

TEST(ConnectionTest, ConstructEchoResponseTest)
{
  boost::asio::io_service io_service_;
  boost::asio::ip::tcp::socket socket_(io_service_);
  
  std::map <std::string, RequestHandler*> handlers;
  NginxConfig echo_config;

  handlers["/echo"] = RequestHandler::CreateByName("EchoHandler");
  handlers["/echo"]->Init("", echo_config);

  auto my_connection = std::make_shared<http::server::connection>(std::move(socket_), handlers);

  std::string raw_request = 
                "GET /echo HTTP/1.1\r\n"
                "Host: localhost:1080\r\n"
                "User-Agent: Mozilla/5.0\r\n"
                "Accept: text/html\r\n\r\n";
  
  Request req = my_connection->call_parser(raw_request);
  RequestHandler* handler = my_connection->find_handler(req);
  RequestHandler::Status status = my_connection->call_handler(handler);

  Response res = my_connection->get_response();

  std::string response = 
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 88\r\n\r\n" 
                + raw_request;

  EXPECT_EQ(res.ToString(), response);
  EXPECT_EQ(handlers["/echo"], handler);
  EXPECT_EQ(status, 0);
}

} // namespace server
} // namespace http