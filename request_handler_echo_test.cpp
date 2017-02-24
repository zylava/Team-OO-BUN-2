#include "gtest/gtest.h"
#include "connection.h"
#include "gmock/gmock.h"
#include <boost/asio.hpp>
#include "request_handler.h"

namespace http {
namespace server {

TEST(HandlerEchoTest, InitStatusTest)
{
	RequestHandler* handler = RequestHandler::CreateByName("EchoHandler");
	NginxConfig echo_config;
	RequestHandler::Status status = handler->Init("", echo_config);

	EXPECT_EQ(status, 0);
}

TEST(HandlerEchoTest, HandleRequestStatusTest)
{
	RequestHandler* handler = RequestHandler::CreateByName("EchoHandler");
	NginxConfig echo_config;
	handler->Init("", echo_config);

	std::string raw_request = "GET /echo HTTP/1.1\r\n\r\n";

	auto request = Request::Parse(raw_request); 

	Request req = *request;
	Response res;

	RequestHandler::Status status = handler->HandleRequest(req, &res);

	EXPECT_EQ(status, 0);
}

TEST(HandlerEchoTest, HandleRequestResultTest)
{
	RequestHandler* handler = RequestHandler::CreateByName("EchoHandler");
	NginxConfig echo_config;
	handler->Init("", echo_config);

	std::string raw_request = 
		"GET /echo HTTP/1.1\r\n"
	 	"Host: localhost:2020\r\n"
		"User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:44.0) Gecko/20100101 Firefox/44.0\r\n"
		"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
		"Accept-Language: en-US,en;q=0.5\r\n"
		"Accept-Encoding: gzip, deflate\r\n"
		"Connection: keep-alive\r\n\r\n";

	auto request = Request::Parse(raw_request); 

	Request req = *request;
	Response res;

	RequestHandler::Status status = handler->HandleRequest(req, &res);

	std::string response = 
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/plain\r\n"
		"Content-Length: 296\r\n\r\n" 
		+ raw_request;

	EXPECT_EQ(res.ToString(), response);
	EXPECT_EQ(status, 0);
}

} // namespace server
} // namespace http