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

#include "persona.h"
#include "alumno.h"
#include "gtest/gtest.h"

TEST(Persona, PersonaOP) {
  Persona p("AX45");

  EXPECT_EQ("AX45", p.getNombre());
  p.setNombre("LL89");
  EXPECT_EQ("LL89", p.getNombre());
}

TEST(Alumno, AlumnoOP) {
  Alumno a("XT55", 45);
  EXPECT_EQ("XT55", a.getNombre());
  EXPECT_EQ(1, a.getCurso());
  a.setNombre("99YY");
  EXPECT_EQ("99YY", a.getNombre());
  EXPECT_FALSE(a.setCurso(55));
  EXPECT_TRUE(a.setCurso(2));
  EXPECT_EQ(2,a.getCurso());
}

TEST(Alumno, Herencia) {
  Alumno a("KO55", 45);
  EXPECT_EQ("KO55", a.Persona::getNombre());
  a.Persona::setNombre("HH88");
  EXPECT_EQ("HH88", a.Persona::getNombre());
}
