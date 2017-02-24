#ifndef STATUS_HANDLER_H
#define STATUS_HANDLER_H

#include "request_handler.h"
#include "server_monitor.h"
#include <iostream> 
#include <stdio.h>
#include <string> 

namespace http {
	namespace server {
		class StatusHandler : public RequestHandler {
		public: 
			Status Init(const std::string& uri_prefix, const NginxConfig& config) override;

  			Status HandleRequest(const Request& request, Response* response) override;
		};

		REGISTER_REQUEST_HANDLER(StatusHandler);
	} // namespace server
} // namespace http

#endif  // STATUS_HANDLER_H