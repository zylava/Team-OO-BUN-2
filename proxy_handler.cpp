#include "proxy_handler.h"
#include <string>
#include <vector>

namespace http {
  namespace server {

    RequestHandler::Status ProxyHandler::Init(const std::string& uri_prefix, const NginxConfig& config) {

        mUri_prefix = uri_prefix;

        std::vector<std::shared_ptr<NginxConfigStatement>> statements = config.statements_;
        for (unsigned int j = 0; j < statements.size(); ++j) {
          for (unsigned int k = 0; k < statements[j]->tokens_.size(); ++k) {
            if (statements[j]->tokens_[k]=="url") {
              mURL = statements[j]->tokens_[k+1];
	      normalizeURL();
            }
          }
        }

        //TODO: error handling for empty prefix
        return Status::OK;
    }

    RequestHandler::Status ProxyHandler::HandleRequest(const Request& request, Response* response) {
        std::cout << "ProxyHandler::HandleRequest called" << std::endl;

	std::cout << "request uri: " << request.uri().substr(mUri_prefix.length()) << std::endl;
	std::cout << "mUri_prefix: " << mUri_prefix << std::endl;
	std::cout << mURL << std::endl;
	response->SetStatus(Response::ResponseCode::REDIRECT);
	response->AddHeader("Location", mURL);
 

        return RequestHandler::Status::OK;
      }
    //to make sure url that doesn't start with https://www. is prefixed with that (if url is 127.0.0.1, then leave it alone)
    void ProxyHandler::normalizeURL() {
      int colonPos = mURL.find(':');
      std::string host = mURL.substr(0, colonPos);
      if (host != "127.0.0.1") {
        int dotPos = mURL.find('.');
        std::string head = mURL.substr(0, dotPos);
        if (head.substr(head.length() - 3, 3).length() < 3 || head.substr(head.length() - 3, 3) != "www") {
          mURL = "https://www." + mURL; 
        }
        else {
	  mURL = "https://www." + mURL.substr(dotPos + 1);
        }
      }
    }
  } // namespace server
} // namespace https


