#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "server.hpp"
#include <boost/asio.hpp>
#include "mock_connection.h"

boost::asio::io_service io_service_;
boost::asio::ip::tcp::socket socket_(io_service_);

TEST(ServerTest, RunTest) {
	http::server::server s("localhost", "3000", ".");
	s.run(); 

	EXPECT_TRUE(s.getStatus()); 
}

TEST(ServerTest, CorrectInfoTest) {
	http::server::server s("localhost", "3000", "."); 

	EXPECT_EQ("3000", s.getPortNum());
	EXPECT_EQ("localhost", s.getAddress()); 
	EXPECT_EQ(".", s.getFileName()); 
}

TEST(ServerTest, MockTest) {
	//MockConnection mock_connection(std::move(socket_));
	EXPECT_TRUE(true);
}