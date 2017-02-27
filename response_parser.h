#ifndef RESPONSE_PARSER_H
#define RESPONSE_PARSER_H

class ResponseParser{
public:
	ReponseParser(){
		redirect_url = "";
	}

	int parse_response(std::string response);
	int get_response_code();
	int get_content_length();
	std::string get_redirect_url();
private:
	int response_code;
	int content_length;
	std::string redirect_url;
	bool is_a_number(const std::string s);
	std::string find_response_code(std::string response);
	std::string find_header_value(std::string header, std::string response);
}

#endif