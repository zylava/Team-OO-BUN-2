#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <boost/asio.hpp>
#include "request_handler.h"
#include <string> 

TEST(ResponseTest, ResponseOKTest)
{
	std::string s= "This is my testing string"; 
	http::server::Response r;
  	r.SetStatus(http::server::Response::OK);
  	r.SetBody(s);
  	r.AddHeader("Content-Type", "text/plain");
	r.AddHeader("Content-Length", std::to_string(s.length()));

	std::string expected_string = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 25\r\n\r\n";
	expected_string += s; 

	EXPECT_EQ(expected_string, r.ToString()); 
}

TEST(ResponseTest, ResponseNOTFOUNDTest)
{
	std::string s= "This is my testing string"; 
	http::server::Response r;
  	r.SetStatus(http::server::Response::NOT_FOUND);
  	r.SetBody(s);
  	r.AddHeader("Content-Type", "text/plain");
	r.AddHeader("Content-Length", std::to_string(s.length()));

	std::string expected_string = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nContent-Length: 25\r\n\r\n";
	expected_string += s; 

	EXPECT_EQ(expected_string, r.ToString()); 
}


TEST(ResponseTest, ResponseBADREQUESTTest)
{
	std::string s= "This is my testing string"; 
	http::server::Response r;
  	r.SetStatus(http::server::Response::BAD_REQUEST);
  	r.SetBody(s);
  	r.AddHeader("Content-Type", "text/plain");
	r.AddHeader("Content-Length", std::to_string(s.length()));

	std::string expected_string = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 25\r\n\r\n";
	expected_string += s; 

	EXPECT_EQ(expected_string, r.ToString()); 
}

