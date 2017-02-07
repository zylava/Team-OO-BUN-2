#include <iostream> 
#include <stdio.h>
using namespace std;

#include "ngnix/config_parser.h"
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

  string port_number = "";
  string static_root = "";
  string echo_handler = "";
  string static_handler = "";

  for (const auto& statement : config.statements_) {
    for (unsigned int i = 0; i < statement->tokens_.size(); ++i) {

      if (statement->tokens_[i] == "port")
        port_number = statement->tokens_[i+1];

      else if (statement->tokens_[i]=="path" && statement->tokens_[i+1]=="/static"){
        static_handler = statement->tokens_[i+2];
        std::vector<std::shared_ptr<NginxConfigStatement>> statements = 
                                statement->child_block_->statements_;
        for (unsigned int j = 0; j < statements.size(); ++j) {
          for (unsigned int k = 0; k < statements[i]->tokens_.size(); ++k) {
            if (statements[j]->tokens_[k]=="root")
              static_root = statements[j]->tokens_[k+1];
          }
        }
      }

      else if (statement->tokens_[i]=="path" && statement->tokens_[i+1]=="/echo"){
        echo_handler = statement->tokens_[i+2];
      }

    }
  }

  //parses the config file for the port number 
  // string parse_string = config.ToString().c_str();
  // string port_number = boost::regex_replace(
  //   parse_string,
  //   boost::regex("[^0-9]*([0-9]+).*"),
  //   string("\\1")
  //   );
  // string path = "";
  // string root = "";

  if ( static_root.front() == '"' || static_root.front()=='\'' ) {
    static_root.erase( 0, 1 ); // erase the first character
  }
  if ( static_root.back() == '"' || static_root.back()=='\'') {
    static_root.erase( static_root.size() - 1 ); // erase the last character
  }

  cout << endl << "port_number: " << port_number << endl;
  cout << "static_root: " << static_root << endl;
  cout << "static_handler: " << static_handler << endl;
  cout << "echo_handler: " << echo_handler << endl;

  http::server::server s("localhost", port_number, static_root);

  s.run();
  return 0;
}