// For the Request and Response classes, you need to implement the methods
// and add private data as appropriate. You may also need to modify or extend
// the API when implementing the reverse proxy. Use your good judgment.
#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <map>
#include <memory>
#include <string>
#include "ngnix/config_parser.h"

// Represents an HTTP Request.
//
// Usage:
//   auto request = Request::Parse(raw_request);

namespace http {
  namespace server {

class Request {
 public:
  static std::unique_ptr<Request> Parse(const std::string& raw_request);

  // Getters
  std::string raw_request() const { return m_raw_request; }
  std::string method() const { return m_method; }
  std::string uri() const { return m_uri; };
  std::string version() const { return m_version; }

  using Headers = std::vector<std::pair<std::string, std::string>>;
  Headers headers() const { return m_headers; }

  std::string body() const { return m_body; }

 private:
  std::string m_raw_request;
  std::string m_method;
  std::string m_uri;
  std::string m_version;
  std::string m_body;

  Headers m_headers;

};

// Represents an HTTP response.
//
// Usage:
//   Response r;
//   r.SetStatus(RESPONSE_200);
//   r.SetBody(...);
//   return r.ToString();
//
// Constructed by the RequestHandler, after which the server should call ToString
// to serialize.
class Response {
 public:
  enum ResponseCode {
    // Define your HTTP response codes here.
    OK = 200,
    BAD_REQUEST = 400,
    NOT_FOUND = 404,
    REDIRECT = 302
  };
  
  void SetStatus(const ResponseCode response_code);
  void AddHeader(const std::string& header_name, const std::string& header_value);
  void SetBody(const std::string& body);
  
  ResponseCode GetStatus();   

  std::string ToString();

  private:
    ResponseCode responseStatus; 
    std::string content; 
    std::vector<std::pair<std::string, std::string>> mHeaders;
    std::string mVersion;
};

// Represents the parent of all request handlers. Implementations should expect to
// be long lived and created at server constrution.
class RequestHandler {
 public:
  enum Status {
    OK = 0,
    BAD_REQUEST = 1,
    NOT_FOUND = 2
    // Define your status codes here.
  };
  
  // Initializes the handler. Returns a response code indicating success or
  // failure condition.
  // uri_prefix is the value in the config file that this handler will run for.
  // config is the contents of the child block for this handler ONLY.
  virtual Status Init(const std::string& uri_prefix,
                      const NginxConfig& config) = 0;

  // Handles an HTTP request, and generates a response. Returns a response code
  // indicating success or failure condition. If ResponseCode is not OK, the
  // contents of the response object are undefined, and the server will return
  // HTTP code 500.
  virtual Status HandleRequest(const Request& request,
                               Response* response) = 0;

  static RequestHandler* CreateByName(const char* type);

  // private:
    std::string mUri_prefix;
    std::string mPath; 
    std::string mHandlerName; 
    std::string mRoot;
    std::string mURL;  
};

extern std::map<std::string, RequestHandler* (*)(void)>* request_handler_builders;
template<typename T>
class RequestHandlerRegisterer {
 public:
  RequestHandlerRegisterer(const std::string& type) {
    if (request_handler_builders == nullptr) {
      request_handler_builders = new std::map<std::string, RequestHandler* (*)(void)>;
    }
    (*request_handler_builders)[type] = RequestHandlerRegisterer::Create;
  }
  static RequestHandler* Create() {
    return new T;
  }
};


#define REGISTER_REQUEST_HANDLER(ClassName) \
  static RequestHandlerRegisterer<ClassName> ClassName##__registerer(#ClassName)
  
} // namespace server
} // namespace http

#endif  // REQUEST_HANDLER_H
