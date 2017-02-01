GTEST_DIR=../ngnix/googletest/googletest
GMOCK_DIR=../ngnix/googletest/googlemock

all: echo_server

echo_server: echo_server.cc ../ngnix/config_parser.cc server.cpp connection.cpp
	g++ echo_server.cc ../ngnix/config_parser.cc server.cpp connection.cpp \
	-std=c++0x -g -Wall -lboost_regex -lboost_system -lpthread -o webserver

test: server_test.cc connection_test.cc server.cpp ${GTEST_DIR}/src/gtest-all.cc connection.cpp ${GTEST_DIR}/src/gtest_main.cc ${GMOCK_DIR}/src/gmock-all.cc
	g++ server_test.cc connection_test.cc server.cpp -isystem ${GTEST_DIR}/include \
	-I${GTEST_DIR} ${GTEST_DIR}/src/gtest-all.cc connection.cpp ${GTEST_DIR}/src/gtest_main.cc \
	-isystem ${GMOCK_DIR}/include -I${GMOCK_DIR} ${GMOCK_DIR}/src/gmock-all.cc \
	-std=c++0x -g -Wall -lboost_regex -lboost_system -lpthread -o mytest

gcov: server_test.cc connection_test.cc server.cpp ${GTEST_DIR}/src/gtest-all.cc connection.cpp ${GTEST_DIR}/src/gtest_main.cc ${GMOCK_DIR}/src/gmock-all.cc
	g++ server_test.cc connection_test.cc server.cpp -isystem ${GTEST_DIR}/include \
	-I${GTEST_DIR} ${GTEST_DIR}/src/gtest-all.cc connection.cpp ${GTEST_DIR}/src/gtest_main.cc \
	-isystem ${GMOCK_DIR}/include -I${GMOCK_DIR} ${GMOCK_DIR}/src/gmock-all.cc \
	-std=c++0x -g -Wall -lboost_regex -lboost_system -fprofile-arcs -ftest-coverage -lpthread -o gcov_test

integration: integration_test.sh
	./integration_test.sh

clean:
	rm -rf *.o webserver