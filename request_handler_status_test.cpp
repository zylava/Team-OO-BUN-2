#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <boost/asio.hpp>
#include "request_handler_status.h"

namespace http {
namespace server {

	TEST(StatusHandlerTest, InitTest)
	{
		RequestHandler* statusHandler = RequestHandler::CreateByName("StatusHandler");
		NginxConfig status_config;
		RequestHandler::Status status = statusHandler->Init("/status", status_config);

		EXPECT_EQ(status, RequestHandler::Status::OK);
	}

	TEST(StatusHandlerTest, HandleRequestTest)
	{
		RequestHandler* statusHandler = RequestHandler::CreateByName("StatusHandler");
		NginxConfig status_config;
		statusHandler->Init("/status", status_config);
		ServerMonitor::getInstance()->addHandler("EchoHandler", "/echo"); 

		ServerMonitor::getInstance()->addRequest("/echo", Response::OK);

		Request request; 
		Response response; 
		RequestHandler::Status status = statusHandler->HandleRequest(request, &response); 
		EXPECT_EQ(status, RequestHandler::Status::OK);

		std::vector<std::pair<std::string, Response::ResponseCode>> requests = ServerMonitor::getInstance()->getRequests();
    	std::vector<std::pair<std::string, std::string>> handlers = ServerMonitor::getInstance()->getHandlers();

    	int numRequests = requests.size(); 
    	std::string expected_string = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 188\r\n\r\n";
  		std::string body = "<html><body><h1>";
  		body += "There were " + to_string(numRequests) + " requests done on this server</h1>";
  		body += "<p>"; 
  		for(auto iterator = requests.begin(); iterator != requests.end(); iterator++) {
  		  std::string responseString = "";
		  switch(iterator->second) {
			case Response::OK:
				responseString += "200";
				break; 
			case Response::BAD_REQUEST: 
				responseString += "400";
				break;
			case Response::NOT_FOUND:
				responseString += "404";
				break;
		  }

  		  body += iterator->first + " " +  responseString + "<br>"; 
      	}
      	body += "</p>"; 

      	body += "<h1> These are the current handlers and their URL prefixes </h1><p>"; 
      	for(auto iterator = handlers.begin(); iterator != handlers.end(); iterator++) {
		  body += iterator->first + " " +  iterator->second + "<br>"; 
      	}
      	body += "</p>"; 
      	body += "</body></html>"; 
      	expected_string += body; 
      	EXPECT_EQ(response.ToString(), expected_string);
	}
}
}