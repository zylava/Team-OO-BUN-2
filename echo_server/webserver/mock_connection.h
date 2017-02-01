#ifndef MOCKCONNECTION_H
#define MOCKCONNECTION_H

#include "gmock/gmock.h" 
#include "connection.hpp"

class connection; 

class MockConnection : public connection {
	public: 
		MOCK_METHOD0(start, void()); 
		MOCK_METHOD0(stop, void()); 
		MOCK_METHOD0(do_read, void()); 
		MOCK_METHOD2(write_response, void()); 
};

#endif 