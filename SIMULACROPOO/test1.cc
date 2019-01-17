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
#include "dado.h"
#include "gtest/gtest.h"

TEST(Dado, Constructor1) {
  Dado d;
  EXPECT_EQ(1, d.get());
}

TEST(Dado, Constructor2) {
  Dado d(3);
  EXPECT_EQ(3, d.get());
}

TEST(Dado, Constructor3) {
  Dado d(99);
  EXPECT_EQ(1, d.get());
}

TEST(Dado, Modificador) {
  Dado d;
  EXPECT_FALSE(d.set(-5));
  EXPECT_FALSE(d.set(12));
  EXPECT_FALSE(d.set(0));
  EXPECT_FALSE(d.set(-1));
  EXPECT_TRUE(d.set(1));
  EXPECT_EQ(1, d.get());
  EXPECT_TRUE(d.set(5));
  EXPECT_EQ(5, d.get());
  EXPECT_TRUE(d.set(6));
  EXPECT_EQ(6, d.get());
}

TEST(Dado, Operator1) {
  Dado d1(3),d2(5);
  EXPECT_EQ(8, d1+d2);

}

TEST(Dado, Operator2) {
  srand(time(NULL));
  int x,y;
  x=(rand()%6)+1;
  y=(rand()%6)+1;
  Dado d1(x),d2(y);
  EXPECT_EQ(x+y, d1+d2);
}
