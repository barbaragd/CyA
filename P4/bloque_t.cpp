#include "bloque_t.hpp"
#include <iostream>

using namespace std;

bloque_t::bloque_t(int tamano): tamano_(tamano){
}

void bloque_t::write(ostream& os) const
{
	for(int i=0; i<tamano_; i++){
		os << "x";
	}
}

int bloque_t::get_tamano(){
	return tamano_;
}	




ostream& operator<<(ostream& os, const bloque_t& bloque){
    bloque.write(os);
    return os;
}
