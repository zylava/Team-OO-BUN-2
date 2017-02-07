#include "gtest/gtest.h"
#include "request_handler.h"
#include "gmock/gmock.h"
#include <boost/asio.hpp>
#include <string> 
#include "reply.h" 
#include "request.hpp"
#include <iostream> 

TEST(RequestHandlerTest, HandleRequestNotFound) {

	std::string doc_root = ".";
	http::server::request_handler request_handler_tester(doc_root); 

	http::server::request my_request;
	//form out my test request
	my_request.method = "GET"; 
	my_request.uri = "/my_test_dir/my_test.html"; //Expecting 404 Not Found since it is not a real file
	my_request.http_version_major = 0;
	my_request.http_version_minor = 0; 

	http::server::reply my_reply;

	request_handler_tester.handle_request(my_request, my_reply); 

	std::string expected_response = "<html><head><title>Not Found</title></head><body><h1>404 Not Found</h1></body></html>"; //404 Not Found in HTML format

	std::string response_length = std::to_string(expected_response.length());
	EXPECT_EQ(my_reply.content, expected_response); 
	EXPECT_EQ(my_reply.headers[0].name, "Content-Length");
	EXPECT_EQ(my_reply.headers[0].value, response_length.c_str()); 
	EXPECT_EQ(my_reply.headers[1].name, "Content-Type"); 
	EXPECT_EQ(my_reply.headers[1].value, "text/html");
}

TEST(RequestHandlerTest, HandleGoodRequest) {

	std::string doc_root = ".";
	http::server::request_handler request_handler_tester(doc_root); 

	http::server::request my_request;
	//form out my test request
	my_request.method = "GET"; 
	my_request.uri = "/index.html"; //should return our default: index.html 
	my_request.http_version_major = 0;
	my_request.http_version_minor = 0; 

	http::server::reply my_reply;

	request_handler_tester.handle_request(my_request, my_reply); 

	std::string expected_response = "<html><h1>Usage: /echo for echo server</h1><h1>Usage: /filePath to serve static files</h1></html>"; //Our index.html content

	std::string response_length = std::to_string(expected_response.length());

	EXPECT_EQ(my_reply.content, expected_response); 
	EXPECT_EQ(my_reply.headers[0].name, "Content-Length");
	EXPECT_EQ(my_reply.headers[0].value, response_length.c_str()); 
	EXPECT_EQ(my_reply.headers[1].name, "Content-Type"); 
	EXPECT_EQ(my_reply.headers[1].value, "text/html"); 
}

TEST(RequestHandlerTest, HandleBadRequest) {

	std::string doc_root = ".";
	http::server::request_handler request_handler_tester(doc_root); 

	http::server::request my_request;
	//form my test request
	my_request.method = "GET"; 
	my_request.uri = "index[html"; //should return a bad request
	my_request.http_version_major = 0;
	my_request.http_version_minor = 0; 

	http::server::reply my_reply;

	request_handler_tester.handle_request(my_request, my_reply); 

	std::string expected_response = "<html><head><title>Bad Request</title></head><body><h1>400 Bad Request</h1></body></html>"; //Bad request

	std::string response_length = std::to_string(expected_response.length());

	EXPECT_EQ(my_reply.content, expected_response); 
	EXPECT_EQ(my_reply.headers[0].name, "Content-Length");
	EXPECT_EQ(my_reply.headers[0].value, response_length.c_str()); 
	EXPECT_EQ(my_reply.headers[1].name, "Content-Type"); 
	EXPECT_EQ(my_reply.headers[1].value, "text/html"); 
}
