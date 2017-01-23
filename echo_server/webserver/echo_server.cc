#include <iostream> 
#include <stdio.h>
using namespace std;

#include "../ngnix/config_parser.h"
#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include "server.hpp"


int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Usage: ./config_parser <path to config file>\n");
    return 1;
  }

  NginxConfigParser config_parser;
  NginxConfig config;
  config_parser.Parse(argv[1], &config);

  string parse_string = config.ToString().c_str();
  string port_number = boost::regex_replace(
    parse_string,
    boost::regex("[^0-9]*([0-9]+).*"),
    string("\\1")
    );


  http::server::server s("localhost", port_number, "index.html");
  s.run();
  return 0;
}
