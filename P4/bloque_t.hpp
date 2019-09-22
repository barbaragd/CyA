#pragma once 
#include <iostream>

using namespace std;

class bloque_t{

	private:
	int tamano_;
	
	public:
	bloque_t(int tamano);
	~bloque_t(){}

	void write(ostream& os) const;
	
	int get_tamano();

};

ostream& operator<<(ostream& os, const bloque_t& bloque);
