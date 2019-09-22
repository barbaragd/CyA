#include "fila_t.hpp"
#include <vector>
#include <iostream>


fila_t::fila_t(int t_m): tam_max_(t_m), tam_act_(0), c_bloques(0){
}

void fila_t::meter_bloque(bloque_t bloque){
	tam_act_ +=bloque.get_tamano();
	fila_.push_back(bloque);
	c_bloques++;
}


void fila_t::sacar_bloque(){
	tam_act_ -= fila_[fila_.size()-1].get_tamano();
	fila_.pop_back();
	c_bloques--;
}


int fila_t::get_tam_max_(){
	return tam_max_;
}

int fila_t::get_tam_act_(){
	return tam_act_;
}

int fila_t::get_c_bloques(){
	return c_bloques;
}

bloque_t fila_t::get_bloque(int pos){
	return fila_[pos];
}



void fila_t::write(ostream& os) const{
	os << "|";
	for(int i=0; i<c_bloques; i++){
		os << fila_[i] << "|";
	}
}

ostream& operator<<(ostream& os, const fila_t& fila){
	fila.write(os);
	return os;
}
