#include "reply.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(ReplyTest, StatusOkTest) {
	http::server::reply rep;
	rep = http::server::reply::stock_reply(http::server::reply::ok);
	EXPECT_EQ(200, rep.status);
	EXPECT_EQ("", rep.content);
}

TEST(ReplyTest, StatusCreatedTest) {
	http::server::reply rep;
	rep = http::server::reply::stock_reply(http::server::reply::created);
	EXPECT_EQ(201, rep.status);
	EXPECT_EQ("<html><head><title>Created</title></head><body><h1>201 Created</h1></body></html>", rep.content);
}

TEST(ReplyTest, StatusAcceptedTest) {
	http::server::reply rep;
	rep = http::server::reply::stock_reply(http::server::reply::accepted);
	EXPECT_EQ(202, rep.status);
}

TEST(ReplyTest, StatusNoContentTest) {
	http::server::reply rep;
	rep = http::server::reply::stock_reply(http::server::reply::no_content);
	EXPECT_EQ(204, rep.status);
}

TEST(ReplyTest, StatusMultipleChoicesTest) {
	http::server::reply rep;
	rep = http::server::reply::stock_reply(http::server::reply::multiple_choices);
	EXPECT_EQ(300, rep.status);
}

TEST(ReplyTest, StatusMovedPermanantelyTest) {
	http::server::reply rep;
	rep = http::server::reply::stock_reply(http::server::reply::moved_permanently);
	EXPECT_EQ(301, rep.status);
}

TEST(ReplyTest, StatusMovedTemporarilyTest) {
	http::server::reply rep;
	rep = http::server::reply::stock_reply(http::server::reply::moved_temporarily);
	EXPECT_EQ(302, rep.status);
}

TEST(ReplyTest, StatusNotModifiedTest) {
	http::server::reply rep;
	rep = http::server::reply::stock_reply(http::server::reply::not_modified);
	EXPECT_EQ(304, rep.status);
}

TEST(ReplyTest, StatusBadRequestTest) {
	http::server::reply rep;
	rep = http::server::reply::stock_reply(http::server::reply::bad_request);
	EXPECT_EQ(400, rep.status);
}

TEST(ReplyTest, StatusUnauthorizedTest) {
	http::server::reply rep;
	rep = http::server::reply::stock_reply(http::server::reply::unauthorized);
	EXPECT_EQ(401, rep.status);
}

TEST(ReplyTest, StatusForbiddenTest) {
	http::server::reply rep;
	rep = http::server::reply::stock_reply(http::server::reply::forbidden);
	EXPECT_EQ(403, rep.status);
}

TEST(ReplyTest, StatusNotFoundTest) {
	http::server::reply rep;
	rep = http::server::reply::stock_reply(http::server::reply::not_found);
	EXPECT_EQ(404, rep.status);
}

TEST(ReplyTest, StatusInternalServerErrorTest) {
	http::server::reply rep;
	rep = http::server::reply::stock_reply(http::server::reply::internal_server_error);
	EXPECT_EQ(500, rep.status);
}

TEST(ReplyTest, StatusNotImplementedTest) {
	http::server::reply rep;
	rep = http::server::reply::stock_reply(http::server::reply::not_implemented);
	EXPECT_EQ(501, rep.status);
}

TEST(ReplyTest, StatusBadGatewayTest) {
	http::server::reply rep;
	rep = http::server::reply::stock_reply(http::server::reply::bad_gateway);
	EXPECT_EQ(502, rep.status);
}

TEST(ReplyTest, StatusServiceUnavailableTest) {
	http::server::reply rep;
	rep = http::server::reply::stock_reply(http::server::reply::service_unavailable);
	EXPECT_EQ(503, rep.status);
}