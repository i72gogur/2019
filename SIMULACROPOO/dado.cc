//dado.cc

#include "dado.h"

Dado::Dado(int d){
	if(d>6 || d<1){
		d_=1;
	}
	else{
		d_=d;
	}
}

bool Dado::set(int d){
	if(d>6 || d<1){
		return false;
	}
	else{
		d_=d;
		return true;
	}
}

int operator+(Dado d1, Dado d2){
	return d1.get()+d2.get();
}