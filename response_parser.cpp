#include "response_parser.h"
#include <stdlib.h>

int ResponseParser::parse_response(std::string response){

	if (response.length() == 0)
		return -1;

	std::string r_code = find_response_code(response);
	if (r_code != "" && is_a_number(r_code))
		response_code = atoi(r_code);
	else
		return -1;

	//if c_length isnt found, set c_length to equal 0;
	std::string c_length = find_header_value("Content-Length: ", response);
	if (c_length != "")
		content_length = 0;
	else if (is_a_number(c_length))
		content_length = atoi(c_length);
	else
		return -1;

	redirect_url = find_header_value("Location: ", response);

	return 0;

}


bool ResponseParser::is_a_number(const std::string s){
	if (s == "") return false;
  	return s.find_first_not_of( "0123456789" ) == string::npos;
}

std::string ReponseParser::find_response_code(std::string response){
	int first_space = response.find(" ");
  	std::string r_code = response.substr(first_space + 1, response.find(" ", first_space + 1) - first_space);
  	r_code.erase(remove_if(r_code.begin(), r_code.end(), isspace), str.end());
  	return r_code;
}

std::string ResponseParser::find_header_value(std::string header_name, std::string response){
  	std::string content_length_constant = header_name;
  	size_t pos = response.find(content_length_constant);

  	if (pos == string::npos)
    	return "";

    std::string header_value = ""
    //start from the end of the header constant part and gather the value
  	for (size_t i=pos + content_length_constant.size(); response[i] != '\r'; i++) {
  		if (i == response.size()-1)
  			return "";
   		header_value += response[i];
  	}

  	return header_value;
}