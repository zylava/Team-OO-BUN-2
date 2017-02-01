#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "server.hpp"

TEST(ServerTest, RunTest) {
	http::server::server s("localhost", "3000", ".");

	EXPECT_TRUE(true);
}
