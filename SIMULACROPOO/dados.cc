//dados.cc

#include "dados.h"

Dados::Dados(int d1, int d2){
	if(d1>6 || d1<1){
		d1_=1;
	}
	else{
		d1_=d1;
	}

	if(d2>6 || d2<1){
		d2_=1;
	}
	else{
		d2_=d2;
	}
}

bool Dados::get(int id, int &valor){
	if(id!=1 && id!=2){
		return false;
	}
	else{
		if(id==1){
			valor=d1_;
			return true;
		}
		else{
			valor=d2_;
			return true;
		}
	}
}

bool Dados::set(int id, int d){
	if(id!=1 && id!=2){
		return false;
	}
	if(d>6 || d<1){
		return false;
	}
	else{
		if(id==1){
			d1_=d;
			return true;
		}
		else{
			d2_=d;
			return true;
		}
	}
}