#include <gtest/gtest.h>
#include <string>
#include "epsol/string.h"

using epsol::string::strip;
using epsol::string::strip_if;

TEST(TestStrip, StripEmptyString) {
    EXPECT_EQ(strip(""), std::string(""));
    EXPECT_EQ(strip(" "), std::string(""));
    EXPECT_EQ(strip("   "), std::string(""));
    EXPECT_EQ(strip("  "), std::string(""));
    EXPECT_EQ(strip("  \n   "), std::string(""));
}

TEST(TestStrip, StripLeaving1Character) {
    EXPECT_EQ(strip("  a   "), std::string("a"));
    EXPECT_EQ(strip("a    "), std::string("a"));
    EXPECT_EQ(strip("   a"), std::string("a"));
    EXPECT_EQ(strip("a "), std::string("a"));
    EXPECT_EQ(strip(" a"), std::string("a"));
    EXPECT_EQ(strip("a"), std::string("a"));
}

TEST(TestStrip, Strip) {
    EXPECT_EQ(strip("\tabc de "), std::string("abc de"));
    EXPECT_EQ(strip("   12345     "), std::string("12345"));
    EXPECT_EQ(strip(" abcde    \n      "), std::string("abcde"));
}
