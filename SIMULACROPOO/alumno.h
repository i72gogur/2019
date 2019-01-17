//alumno.h

#ifndef ALUMNO_H
#define ALUMNO_H

#include "persona.h"
#include <string>

using std::string;

class Alumno : public Persona{
private:
	int curso_;
public:
	Alumno(string nombre, int curso);
	inline int getCurso(){return curso_;};
	bool setCurso(int c);
};

#endif