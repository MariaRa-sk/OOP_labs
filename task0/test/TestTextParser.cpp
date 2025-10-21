#include <gtest/gtest.h>
#include "TextParser.h"

TEST(TextParserTest, ParseBasicLine) {
    TextParser parser;
    const std::vector<std::string> result = parser.parseLine("hello world");
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "hello");
    EXPECT_EQ(result[1], "world");
}

TEST(TextParsetTest, ParseEmptyLine){
    TextParser parser;
    const std::vector<std::string> result = parser.parseLine("");
    EXPECT_EQ(result.size(), 0);
}

TEST(TextParserTest, ParseDelimiters){
    TextParser parser;
    const std::vector<std::string> result = parser.parseLine("!@#$%^&*()_+ /`");
    EXPECT_EQ(result.size(), 0);
}
TEST(TextParserTest, ParseMixedLine){
    TextParser parser;
    const std::vector<std::string> result = parser.parseLine("123 prevet45 medved678!");
    EXPECT_EQ(result.size(),3);
    EXPECT_EQ(result[0], "123");
    EXPECT_EQ(result[1], "prevet45");
    EXPECT_EQ(result[2], "medved678");
}