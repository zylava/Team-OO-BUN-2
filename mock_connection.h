#ifndef MOCKCONNECTION_H
#define MOCKCONNECTION_H

#include "gmock/gmock.h" 
#include "connection.hpp"
#include <boost/asio.hpp>
#include <string>

// boost::asio::io_service io_service_;
// boost::asio::ip::tcp::socket socket_(io_service_);

class MockConnection : public http::server::connection 
{
	public: 
		//MockConnection() : connection(socket_) {}
		//virtual ~MockConnection() {} 
		//explicit MockConnection(boost::asio::ip::tcp::socket& socket_) : connection(socket_) {}
		MOCK_METHOD0(start, void()); 
		MOCK_METHOD0(stop, void()); 
		MOCK_METHOD0(do_read, void()); 
		MOCK_METHOD0(get_response, const char*()); 
		MOCK_METHOD0(get_reply, const char*()); 
		MOCK_METHOD0(getConnectionStatus, int());
		MOCK_METHOD0(write_response, void()); 
		MOCK_METHOD1(construct_response, void(std::string s)); 
		boost::asio::ip::tcp::socket socket_;
};

#endif 