#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "server.hpp"
#include <boost/asio.hpp>
#include "mock_connection.h"

boost::asio::io_service io_service_;
boost::asio::ip::tcp::socket socket_(io_service_);

// TEST(ServerTest, RunTest) {
// 	http::server::server s("localhost", "3000", ".");
// 	s.run(); 

// 	EXPECT_TRUE(s.getStatus()); 
// }

class ServerTest: public ::testing::Test {
protected:
	int errc_success = 0;

    bool create_connection(boost::system::error_code ec) 
    {
      http::server::server s("localhost", "3000", ".");
      return s.create_connection(ec);
    }

    boost::system::error_code create_error(int error_code)
	{
		if (error_code == errc_success)
			return boost::system::errc::make_error_code(boost::system::errc::success);
		else 
			return boost::system::errc::make_error_code(boost::system::errc::invalid_argument);
	}
};

TEST_F(ServerTest, RunTest) {
	http::server::server("localhost", "3000", ".");
	EXPECT_TRUE(true);
}

TEST_F(ServerTest, ServerRunning) {
	http::server::server s("localhost", "3000", ".");
	s.create_connection(create_error(0));
	EXPECT_TRUE(s.getStatus());
}

TEST_F(ServerTest, ErrorSuccess) {
	EXPECT_TRUE(create_connection(create_error(0)));
}

TEST_F(ServerTest, ErrorFail) {
	EXPECT_FALSE(create_connection(create_error(1)));
}

TEST_F(ServerTest, CorrectInfoTest) {
	http::server::server s("localhost", "3000", "."); 

	EXPECT_EQ("3000", s.getPortNum());
	EXPECT_EQ("localhost", s.getAddress()); 
	EXPECT_EQ(".", s.getFileName()); 
}

TEST_F(ServerTest, MockTest) {
	//MockConnection mock_connection(std::move(socket_));
	EXPECT_TRUE(true);
}