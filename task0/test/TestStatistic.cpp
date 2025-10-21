#include <gtest/gtest.h>
#include "Statistic.h"

TEST(StatisticTest, AddSingleWord) {
    Statistic stat;
    stat.addWords({"hello"});
    std::vector<std::string> result = stat.getWords();
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "hello");
    EXPECT_EQ(stat.getCount(result[0]), 1);
    EXPECT_DOUBLE_EQ(stat.getFrequency(result[0]), 100.0);
}

TEST(StatisticTest, ZeroTotalWords) {
    Statistic stat;
    stat.addWords({""});
    std::vector<std::string> result = stat.getWords();
    EXPECT_EQ(result.size(), 0);
}

TEST(StatisticTest, AddMultipleWords) {
    Statistic stat;
    stat.addWords({"hello", "world", "world"});
    std::vector<std::string> result = stat.getWords();
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "world");
    EXPECT_EQ(result[1], "hello");
    EXPECT_EQ(stat.getCount(result[0]), 2);
    EXPECT_EQ(stat.getCount(result[1]), 1);
}

TEST(StatisticTest, DoubleAddCall) {
    Statistic stat;
    stat.addWords({"hello", "world"});
    stat.addWords({"hello", "universe"});
    std::vector<std::string> result = stat.getWords();
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "hello");
    EXPECT_EQ(stat.getCount(result[0]), 2);
}

