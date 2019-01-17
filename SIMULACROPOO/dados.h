//dados.h

class Dados{
private:
	int d1_, d2_;
public:
	Dados(int d1=0, int d2=0);
	bool get(int id, int &valor);
	bool set(int id, int d);
	inline int suma(){return d1_+d2_;};
};