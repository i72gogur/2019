//dado2.h

#ifndef DADO2_H
#define DADO2_H

class Dado{
private:
	int d_, lanzamientos_;
	int vd1_[5];
public:
	Dado(int d=0);
	inline int get(){return d_;};
	bool get(int i, int x);
	bool set(int d);
	//friend int operator+(Dado d1, Dado d2);
	inline int launchs(){return lanzamientos_;};
};

#endif