#include "gtest/gtest.h"
#include "request.hpp"
#include "request_parser.hpp"

class RequestParserTest : public ::testing::Test {
protected:
	http::server::request_parser request_parser_;
	http::server::request_parser::result_type result;
	http::server::request request_;
};

// Check method is parsed
TEST_F(RequestParserTest, MethodTest) {
	std::string input_request = "GET /echo HTTP/1.1\r\nHost: localhost:1080\r\n\r\n";

	std::tie(result, std::ignore) = request_parser_.parse(
          request_, input_request.begin(), input_request.end());

	EXPECT_EQ(request_.method, "GET");
}

// Check that the result of the parsing is good
TEST_F(RequestParserTest, GoodResponseTest) {
	std::string input_request = "GET /echo HTTP/1.1\r\n"
								"Host: localhost:1080\r\n"
								"User-Agent: Mozilla/5.0\r\n"
								"Accept: text/html\r\n\r\n";

	std::tie(result, std::ignore) = request_parser_.parse(
          request_, input_request.begin(), input_request.end());

	EXPECT_EQ(http::server::request_parser::good, result);
}

// Check the parsed header names
TEST_F(RequestParserTest, HeaderNameTest) {
	std::string input_request = "GET /echo HTTP/1.1\r\n"
								"Host: localhost:1080\r\n"
								"User-Agent: Mozilla/5.0\r\n" 
								"Accept: text/html\r\n\r\n";

	http::server::header headers[3];
	headers[0].name = "Host";
	headers[1].name = "User-Agent";
	headers[2].name = "Accept";

	std::tie(result, std::ignore) = request_parser_.parse(
          request_, input_request.begin(), input_request.end());

	for (int i = 0; i < 3; i++)
	{
		EXPECT_EQ(request_.headers[i].name, headers[i].name);
	}
}

// Check the parsed header values
TEST_F(RequestParserTest, HeaderValueTest) {
	std::string input_request = "GET /echo HTTP/1.1\r\n"
								"Host: google.com\r\n"
								"User-Agent: testagent\r\n" 
								"Accept: text/plain\r\n\r\n";

	http::server::header headers[3];
	headers[0].value = "google.com";
	headers[1].value = "testagent";
	headers[2].value = "text/plain";

	std::tie(result, std::ignore) = request_parser_.parse(
          request_, input_request.begin(), input_request.end());

	for (int i = 0; i < 3; i++)
	{
		EXPECT_EQ(request_.headers[i].value, headers[i].value);
	}
}

// Check that the result of the parse is bad
TEST_F(RequestParserTest, BadResponseTest) {
	std::string input_request = "Random line of text here\r\n\r\n";

	std::tie(result, std::ignore)  = request_parser_.parse(
          request_, input_request.begin(), input_request.end());

	EXPECT_FALSE(request_.method == "GET");
	EXPECT_EQ(http::server::request_parser::bad, result);
}

// Check that the result of the parse is indeterminate
TEST_F(RequestParserTest, IndeterminateResponseTest) {
	std::string input_request = "GET /index.html HTTP/1.1";

	std::tie(result, std::ignore)  = request_parser_.parse(
          request_, input_request.begin(), input_request.end());

	EXPECT_TRUE(request_.method == "GET");
	EXPECT_EQ(http::server::request_parser::indeterminate, result);
}