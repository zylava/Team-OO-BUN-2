#include "gtest/gtest.h"
#include "config_parser.h"

TEST(NginxConfigParserTest, SimpleConfig) {
  NginxConfigParser parser;
  NginxConfig out_config;

  bool success = parser.Parse("example_config", &out_config);

  EXPECT_TRUE(success);
}

<<<<<<< HEAD
TEST(NginxConfigParserTest, UnevenBraces){
	NginxConfigParser parser; 
	NginxConfig out_config; 

	bool success = parser.Parse("myexample_config", &out_config); 

	EXPECT_FALSE(success); 
}

class NginxConfigFixtureTest : public ::testing::Test {
public:
 	bool ParseString(const std::string config_string) {
 		std::stringstream config_stream(config_string);
 		return parser_.Parse(&config_stream, &out_config_);
 	}
 	NginxConfigParser parser_;
 	NginxConfig out_config_;
};

TEST_F(NginxConfigFixtureTest, UnevenBraces) {
 EXPECT_FALSE(ParseString("foo bar;}"));
}

TEST_F(NginxConfigFixtureTest, ServerName) {
	EXPECT_TRUE(ParseString("server_name foo.com;"));
	EXPECT_EQ("foo.com", out_config_.statements_.at(0)->tokens_.at(1));
}
=======
class ConfigStringTest : public ::testing::Test {
protected:
	bool ParseString(const std::string config_string) {
		std::stringstream config_stream(config_string);
		return parser_.Parse(&config_stream, &out_config_);
	}
	NginxConfigParser parser_;
	NginxConfig out_config_;
};

TEST_F(ConfigStringTest, StringTest) {
	EXPECT_TRUE(ParseString("foo bar;"));
}

TEST_F(ConfigStringTest, MissingQuote) {
	EXPECT_FALSE(ParseString("\"test"));
}

TEST_F(ConfigStringTest, NoSemi) {
	EXPECT_FALSE(ParseString("lol"));
}

TEST_F(ConfigStringTest, NumStaements) {
	EXPECT_TRUE(ParseString("foo bar; statement;"));
	EXPECT_EQ(2, out_config_.statements_.size());
}

TEST(NginxConfigParserTest, MissingBrace) {
  NginxConfigParser parser;
  NginxConfig out_config;

  bool success = parser.Parse("my_config", &out_config);

  EXPECT_FALSE(success);
}


>>>>>>> master
