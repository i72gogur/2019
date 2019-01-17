//dado2.cc

#include "dado2.h"

Dado::Dado(int d){
	lanzamientos_=0;
	if(d>6 || d<1){
		d_=1;
	}
	else{
		d_=d;
	}
	//lanzamientos_++;

	//inicializamos vector a 0
	for(int i=0; i<5; i++){
		vd1_[i]=0;
	}

	for(int i=0; i<4; i++){
			vd1_[i+1]=vd1_[i];
		}
		vd1_[0]=d_;
}

bool Dado::set(int d){
	if(d>6 || d<1){
		return false;
	}
	else{
		d_=d;
		lanzamientos_++;
		for(int i=0; i<4; i++){
			vd1_[i+1]=vd1_[i];
		}
		vd1_[0]=d_;
		return true;
	}
}

/*int operator+(Dado d1, Dado d2){
	return d1.get()+d2.get();
}*/

bool Dado::get(int i, int x){
	/*if(lanzamientos_<5){
		return false;
	}*/
	if(x>5 || x<0){
		return false;
	}
	if(i>=0 && i<6){
		if(i==0){
			x=d_;
		}
		else{
			x=vd1_[i-1];
		}
		return true;
	}
}