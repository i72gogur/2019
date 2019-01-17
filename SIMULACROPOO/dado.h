//dado.h 

#ifndef DADO_H
#define DADO_H

class Dado{
private:
	int d_;
public:
	Dado(int d=0);
	inline int get(){return d_;};
	bool set(int d);
	friend int operator+(Dado d1, Dado d2);
};

#endif