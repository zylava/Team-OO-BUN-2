#include "request_handler.h" 
#include <sstream>

namespace http {
namespace server {

std::unique_ptr<Request> Request::Parse(const std::string& raw_request) {
    // Create a new request object 
    std::unique_ptr<Request> new_request = std::unique_ptr<Request>(new Request());
    // Set the raw request object
    new_request->m_raw_request = raw_request;

    // Use a string stream to read lines in from the request
    std::stringstream stream;
    stream << raw_request;
    std::vector<std::string> request_lines;

    // Read only if the raw request is not empty
    if (!raw_request.empty()) {
      for (std::string line; std::getline(stream, line, '\n'); ) {
          request_lines.push_back(line);
      }
    }

    // Parse all the lines of the request into their proper member variables
    for (int i = 0; i < (int) request_lines.size(); i++) {
        if (i == 0) {
          // The first line contains the method, uri, and version separated by spaces
          auto find_method = request_lines[i].find(" ");
          new_request->m_method = request_lines[i].substr(0, find_method);
          
          // The GET/POST method is followed by a space
          std::string rest_of_first_line = request_lines[i].substr(find_method + 1);

          // The uri immediately follows the method and a space
          auto find_uri = rest_of_first_line.find(" ");
          new_request->m_uri = rest_of_first_line.substr(0, find_uri);

          // The version is the rest of the first line
          new_request->m_version = rest_of_first_line.substr(find_uri + 1, rest_of_first_line.length() - 1);
        } 
        else if (!request_lines.empty()) {
          // The rest of the request contains a header name, a colon, a space, and its values
          std::size_t colon = request_lines[i].find_first_of(":");

          if (colon != std::string::npos) {
            std::string header_name = request_lines[i].substr(0, colon);

            // The values immediate follow a colon and a space
            std::string header_value = request_lines[i].substr(colon + 2);
            new_request->m_headers.push_back(std::make_pair(header_name, header_value.substr(0, header_value.length() - 1)));
          }
        } 
        else {
          // The rest of the request is the body of the request
          new_request->m_body += request_lines[i];
        }
    }
    return new_request;
  }

} // namespace server
} // namespace http