#include "gtest/gtest.h"
#include "BigInt/BigInt.hpp"

TEST(BigIntTest, Constructors) {
  ACA::BigInt a;          // Default constructor
  ACA::BigInt b("1234");  // String constructor
  ACA::BigInt c(5678);    // unsigned long long constructor
  ACA::BigInt d(b);       // Copy constructor

  EXPECT_EQ(a, ACA::BigInt(0));
  EXPECT_EQ(b, ACA::BigInt("1234"));
  EXPECT_EQ(c, ACA::BigInt(5678));
  EXPECT_EQ(d, b);
}

TEST(BigIntTest, AssignmentOperator) {
  ACA::BigInt a("1234");
  ACA::BigInt b("5678");
  a = b;
  EXPECT_EQ(a, ACA::BigInt("5678"));
  EXPECT_NE(a, ACA::BigInt("1234"));
}

TEST(BigIntTest, ComparisonOperators) {
  ACA::BigInt a("1234");
  ACA::BigInt b("5678");
  ACA::BigInt c("5678");
  ACA::BigInt d("9123");

  EXPECT_TRUE(a < b);
  EXPECT_FALSE(a > b);
  EXPECT_TRUE(b == c);
  EXPECT_TRUE(b <= c);
  EXPECT_FALSE(a == d);
  EXPECT_TRUE(a != d);
  EXPECT_TRUE(d >= b);
  EXPECT_FALSE(d < b);
}

TEST(BigIntTest, IncrementDecrementOperators) {
  ACA::BigInt a("1234");

  EXPECT_EQ(++a, ACA::BigInt("1235"));
  EXPECT_EQ(a++, ACA::BigInt("1235"));
  EXPECT_EQ(a, ACA::BigInt("1236"));

  EXPECT_EQ(--a, ACA::BigInt("1235"));
  EXPECT_EQ(a--, ACA::BigInt("1235"));
  EXPECT_EQ(a, ACA::BigInt("1234"));
}

TEST(BigIntTest, AdditionOperator) {
  ACA::BigInt a("1234");
  ACA::BigInt b("5678");

  EXPECT_EQ(a + b, ACA::BigInt("6912"));
  EXPECT_EQ(b + a, ACA::BigInt("6912"));

  ACA::BigInt c("999999999999999999");
  ACA::BigInt d("1");

  EXPECT_EQ(c + d, ACA::BigInt("1000000000000000000"));
}

TEST(BigIntTest, SubtractionOperator) {
  ACA::BigInt a("5678");
  ACA::BigInt b("1234");

  EXPECT_EQ(a - b, ACA::BigInt("4444"));
  EXPECT_EQ(b - a, ACA::BigInt("-4444"));

  ACA::BigInt c("1000000000000000000");
  ACA::BigInt d("1");

  EXPECT_EQ(c - d, ACA::BigInt("999999999999999999"));
}

int main(){
return 0;
}