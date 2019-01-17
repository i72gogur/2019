//persona.h

#ifndef PERSONA_H
#define PERSONA_H

#include <string>

using std::string;

class Persona{
private:
	string nombre_;
public:
	Persona(string nombre){nombre_=nombre;};
	inline string getNombre(){return nombre_;};
	inline void setNombre(string nombre){nombre_=nombre;};
};

#endif