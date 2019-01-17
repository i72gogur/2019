//alumno.cc

#include "alumno.h"
#include <string>

Alumno::Alumno(string nombre, int curso) : Persona(nombre){
	if(curso>4 || curso<1){
		curso_=1;
	}
	else{
		curso_=curso;
	}
}
bool Alumno::setCurso(int c){
	if(c>4 || c<1){
		return false;
	}
	else{
		curso_=c;
		return true;
	}
}