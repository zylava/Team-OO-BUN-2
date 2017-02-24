#include "request_handler_status.h"

namespace http {
namespace server {

	RequestHandler::Status StatusHandler::Init(const std::string& uri_prefix, const NginxConfig& config) {
		
	return RequestHandler::Status::OK;
	}


	RequestHandler::Status StatusHandler::HandleRequest(const Request& request, Response* response) {
	  	std::cout << "StatusHandler::HandleRequest called" << std::endl;

  		std::vector<std::pair<std::string, Response::ResponseCode>> requests = ServerMonitor::getInstance()->getRequests();
    	std::vector<std::pair<std::string, std::string>> handlers = ServerMonitor::getInstance()->getHandlers();
  		
  		int numRequests = requests.size(); 

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

      	response->SetStatus(Response::ResponseCode::OK);
	  	response->AddHeader("Content-Type", "text/html");
	  	response->AddHeader("Content-Length", std::to_string(body.length()));
	  	response->SetBody(body);

		return RequestHandler::Status::OK;
	}
	
} // namespace server
} // namespace http