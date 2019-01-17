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

#include "dados.h"
#include "gtest/gtest.h"

TEST(Dados, Constructor1) {
  Dados d;
  int d1,d2;
  EXPECT_TRUE(d.get(1,d1));
  EXPECT_TRUE(d.get(2,d2));
  EXPECT_EQ(1, d1);
  EXPECT_EQ(1, d2);
}

TEST(Dados, Constructor2) {
  Dados d(3);
  int d1,d2;
  EXPECT_TRUE(d.get(1,d1));
  EXPECT_TRUE(d.get(2,d2));
  EXPECT_EQ(3, d1);
  EXPECT_EQ(1, d2);
}

TEST(Dados, Constructor3) {
  Dados d(4,5);
  int d1,d2;
  EXPECT_TRUE(d.get(1,d1));
  EXPECT_TRUE(d.get(2,d2));
  EXPECT_EQ(4, d1);
  EXPECT_EQ(5, d2);
}

TEST(Dados, Constructor4) {
  Dados d(1,77);
  int d1,d2;
  EXPECT_TRUE(d.get(1,d1));
  EXPECT_TRUE(d.get(2,d2));
  EXPECT_EQ(1, d1);
  EXPECT_EQ(1, d2);
}

TEST(Dados, Constructor5) {
  Dados d(1,-6);
  int d1,d2;
  EXPECT_TRUE(d.get(1,d1));
  EXPECT_TRUE(d.get(2,d2));
  EXPECT_EQ(1, d1);
  EXPECT_EQ(1, d2);
}

TEST(Dados, Constructor6) {
  Dados d(77, -6);
  int d1,d2;
  EXPECT_TRUE(d.get(1,d1));
  EXPECT_TRUE(d.get(2,d2));
  EXPECT_EQ(1, d1);
  EXPECT_EQ(1, d2);
}

TEST(Dados, Observador) {
  Dados d;
  Dados e(3,6);
  int x;
  EXPECT_FALSE(d.get(-5,x));
  EXPECT_FALSE(d.get(12,x));
  EXPECT_FALSE(d.get(0,x));
  EXPECT_FALSE(d.get(3,x));
  EXPECT_TRUE(d.get(1,x));
  EXPECT_EQ(1, x);
  EXPECT_TRUE(d.get(2,x));
  EXPECT_EQ(1, x);
  EXPECT_TRUE(e.get(1,x));
  EXPECT_EQ(3, x);
  EXPECT_TRUE(e.get(2,x));
  EXPECT_EQ(6, x);
}

TEST(Dados, Modificador) {
  Dados d;
  int x;
  EXPECT_FALSE(d.set(-5,6));
  EXPECT_FALSE(d.set(12,6));
  EXPECT_FALSE(d.set(-5,9));
  EXPECT_FALSE(d.set(12,9));
  EXPECT_FALSE(d.set(1,9));
  EXPECT_FALSE(d.set(2,0));
  EXPECT_FALSE(d.set(0,6));
  EXPECT_FALSE(d.set(1,60));
  EXPECT_FALSE(d.set(2,7));
  EXPECT_TRUE(d.set(1,1));
  EXPECT_TRUE(d.set(2,6));
  EXPECT_TRUE(d.get(1,x));
  EXPECT_EQ(1, x);
  EXPECT_TRUE(d.get(2,x));
  EXPECT_EQ(6, x);
  EXPECT_TRUE(d.set(1,3));
  EXPECT_TRUE(d.set(2,1));
  EXPECT_TRUE(d.get(1,x));
  EXPECT_EQ(3, x);
  EXPECT_TRUE(d.get(2,x));
  EXPECT_EQ(1, x);
}

TEST(Dados, Suma) {
  Dados d;
  EXPECT_EQ(2, d.suma());
  d.set(1,4);
  d.set(2,5);
  EXPECT_EQ(9, d.suma());

  Dados e(2,3);
  EXPECT_EQ(5, e.suma());
  e.set(1,2);
  e.set(2,6);
  EXPECT_EQ(8, e.suma());
}
