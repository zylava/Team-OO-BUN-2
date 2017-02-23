#include "request_handler.h"
#include <string>
#include <vector> 


namespace http {
	namespace server {

		void Response::SetStatus(const ResponseCode response_code) {
			responseStatus = response_code; 
		}

		void Response::AddHeader(const std::string& header_name, const std::string& header_value) {
			mHeaders.push_back(std::make_pair(header_name, header_value));
		}

		void Response::SetBody(const std::string& body) {
			content = body; 
		}

		void Response::SetVersion(const std::string& version) {
			mVersion = version;
		}

		std::string Response::ToString() {
			std::string responseString = ""; 

			switch(responseStatus) {
				case OK:
					responseString += mVersion + " 200 OK\r\n";
					break; 
				case BAD_REQUEST: 
					responseString += mVersion + " 400 Bad Request\r\n";
					break;
				case NOT_FOUND:
					responseString += mVersion + " 404 Not Found\r\n";
					break;
			}

			for(std::vector<std::pair<std::string, std::string>>::const_iterator it = mHeaders.begin(); it != mHeaders.end(); it++){
				responseString += it->first + ": " + it->second + "\r\n"; 
			}

			//need to end headers with carriage return
			responseString += "\r\n"; 

			responseString += content; 

			return responseString; 
		}

  	} // namespace server
} // namespace http