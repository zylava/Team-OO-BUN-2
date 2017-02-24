#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "request_handler_default.h"
#include <boost/asio.hpp>

namespace http{
	namespace server {
		TEST(DefaultHandler, NotFoundStatusTest) {
			const std::string uri_prefix = "/echo";
			NginxConfigParser config_parser;
			NginxConfig config;
			config_parser.Parse("config", &config);
			NotFoundHandler test;
			RequestHandler::Status status = test.Init(uri_prefix, config);
			EXPECT_EQ(status, RequestHandler::Status::NOT_FOUND);
		}

		TEST(DefaultHandler, DefaultHandleRequestTest) {
			Request request;
			Response response;
			NotFoundHandler test;
			RequestHandler::Status status = test.HandleRequest(request, &response);
			EXPECT_EQ(status, RequestHandler::Status::NOT_FOUND);
		}
	}
}

