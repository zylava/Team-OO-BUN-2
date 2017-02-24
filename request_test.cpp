#include "gtest/gtest.h"
#include "connection.h"
#include "gmock/gmock.h"
#include <boost/asio.hpp>
#include "request_handler.h"

TEST(RequestTest, RequestResultTest)
{
  	std::string raw_request = "GET /echo HTTP/1.1\r\n";

	auto request = http::server::Request::Parse(raw_request); 

	http::server::Request req = *request;

	EXPECT_EQ(req.raw_request(), raw_request);
	EXPECT_EQ(req.method(), "GET");
	EXPECT_EQ(req.uri(), "/echo");
	EXPECT_EQ(req.body(), "");
}

TEST(RequestTest, RequestHeaderTest)
{
  	std::string raw_request = "GET /echo HTTP/1.1\r\n"
	 	"Host: localhost:2020\r\n"
		"User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:44.0) Gecko/20100101 Firefox/44.0\r\n"
		"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
		"Accept-Language: en-US,en;q=0.5\r\n"
		"Accept-Encoding: gzip, deflate\r\n"
		"Connection: keep-alive\r\n\r\n";

	auto request = http::server::Request::Parse(raw_request); 

	http::server::Request req = *request;

	using Headers = std::vector<std::pair<std::string, std::string>>;
	Headers head = req.headers();

	std::pair<std::string, std::string> first_header = std::make_pair("Host", "localhost:2020");
	std::pair<std::string, std::string> fourth_header = std::make_pair("Accept-Encoding", "gzip, deflate");
	std::pair<std::string, std::string> fifth_header = std::make_pair("Connection", "keep-alive");
	
	EXPECT_EQ(head[0], first_header);
	EXPECT_EQ(head[4], fourth_header);
	EXPECT_EQ(head[5], fifth_header);
}

TEST(RequestTest, VersionTest)
{
  	std::string raw_request = "GET /echo HTTP/1.1";

	auto request = http::server::Request::Parse(raw_request); 

	http::server::Request req = *request;

	EXPECT_EQ(req.version(), "HTTP/1.1");
}

TEST(RequestTest, URITest)
{
  	std::string raw_request = "GET /static HTTP/1.1";

	auto request = http::server::Request::Parse(raw_request); 

	http::server::Request req = *request;

	EXPECT_EQ(req.uri(), "/static");
	EXPECT_EQ(req.version(), "HTTP/1.1");
}

TEST(RequestTest, MethodTest)
{
  	std::string raw_request = "POST /static HTTP/1.1";

	auto request = http::server::Request::Parse(raw_request); 

	http::server::Request req = *request;

	EXPECT_EQ(req.method(), "POST");
	EXPECT_EQ(req.version(), "HTTP/1.1");
}