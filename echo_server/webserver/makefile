all: echo_server

echo_server: echo_server.cc ../ngnix/config_parser.cc server.cpp connection.cpp
	g++ echo_server.cc ../ngnix/config_parser.cc server.cpp connection.cpp \
	-std=c++0x -g -Wall -lboost_regex -lboost_system -lpthread -o webserver

clean:
	rm -rf *.o webserver