// Juan A. Romero
// A sample program demonstrating using Google C++ testing framework.
//


// This sample shows how to write a more complex unit test for a class
// that has multiple member functions.
//
// Usually, it's a good idea to have one test for each method in your
// class.  You don't have to do that exactly, but it helps to keep
// your tests organized.  You may also throw in additional tests as
// needed.

#include <cstdlib>
#include "dado2.h"
#include "gtest/gtest.h"

TEST(Dado, Constructor1) {
  Dado d;
  EXPECT_EQ(0, d.launchs());
}

TEST(Dado, Constructor2) {
  Dado d;
  d.set(1);
  d.set(2);
  d.set(3);
  EXPECT_EQ(3, d.launchs());
}

TEST(Dado, get1) {
  Dado d;
  int x;
  EXPECT_TRUE(d.get(0,x));
  EXPECT_EQ(1, x);
  EXPECT_TRUE(d.get(1,x));
  EXPECT_EQ(0, x);
  EXPECT_TRUE(d.get(2,x));
  EXPECT_EQ(0, x);
  EXPECT_TRUE(d.get(3,x));
  EXPECT_EQ(0, x);
  EXPECT_TRUE(d.get(4,x));
  EXPECT_EQ(0, x);
  EXPECT_TRUE(d.get(5,x));
  EXPECT_EQ(0, x);
}

TEST(Dado, get2) {
  Dado d;
  int x;
  EXPECT_FALSE(d.get(-2,x));
  EXPECT_FALSE(d.get(7,x));
}

TEST(Dado, get3) {
  Dado d;
  int x;
  d.set(1);
  d.set(2);
  d.set(3);
  d.set(4);
  d.set(5);
  d.set(4);
  d.set(3);
  d.set(2);
  EXPECT_TRUE(d.get(0,x));
  EXPECT_EQ(2, x);
  EXPECT_TRUE(d.get(1,x));
  EXPECT_EQ(3, x);
  EXPECT_TRUE(d.get(2,x));
  EXPECT_EQ(4, x);
  EXPECT_TRUE(d.get(3,x));
  EXPECT_EQ(5, x);
  EXPECT_TRUE(d.get(4,x));
  EXPECT_EQ(4, x);
  EXPECT_TRUE(d.get(5,x));
  EXPECT_EQ(3, x);
}
