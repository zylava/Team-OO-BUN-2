#ifndef DEFAULT_HANDLER_H
#define DEFAULT_HANDLER_H

#include "request_handler.h"
#include <iostream> 

namespace http {
	namespace server {
		class NotFoundHandler : public RequestHandler {
		public: 
			Status Init(const std::string& uri_prefix, const NginxConfig& config) override;

  			Status HandleRequest(const Request& request, Response* response) override;
		};

		REGISTER_REQUEST_HANDLER(NotFoundHandler);
	} // namespace server
} // namespace http

#endif  // ECHO_HANDLER_H