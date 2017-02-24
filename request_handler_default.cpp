#include "request_handler_default.h"

namespace http {
namespace server {

	RequestHandler::Status NotFoundHandler::Init(const std::string& uri_prefix, const NginxConfig& config) {
  	
  	return RequestHandler::Status::NOT_FOUND;
	}


	RequestHandler::Status NotFoundHandler::HandleRequest(const Request& request, Response* response) {
    	std::cout << "NotFoundHandler::HandleRequest called" << std::endl;

    	std::string not_found_response = "<html><body><h1>404 Not Found</h1></body></html>";
    	response->SetStatus(Response::ResponseCode::NOT_FOUND);
	  	response->AddHeader("Content-Type", "text/html");
	  	response->AddHeader("Content-Length", std::to_string(not_found_response.length()));
	  	response->SetBody(not_found_response);
	  	
	return RequestHandler::Status::NOT_FOUND;
  	}
} // namespace server
} // namespace http
