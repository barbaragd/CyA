#include "muro_t.hpp"


using namespace std;

muro_t::muro_t(int ancho, int alto): ancho_(ancho), alto_(alto), altura_actual_(0){
}



int muro_t::get_ancho(){
	return ancho_;
}

int muro_t::get_alto(){
	return alto_;
}

int muro_t::get_altura_actual(){
	return altura_actual_;
}


void muro_t::meter_fila(fila_t fila){
	altura_actual_++;
	muro_.push_back(fila);
}


void muro_t::sacar_fila(){
	altura_actual_--;
	muro_.pop_back();
}

fila_t muro_t::get_fila(int pos){
	return muro_[pos];
}

int muro_t::get_c_bloques(){
	int c_bloques = 0;
	for(int i=0; i<alto_; i++){
		c_bloques += muro_[i].get_c_bloques();
	}
	return c_bloques;
}




bool muro_t::comparar_filas(fila_t a, fila_t b){
	int sum_a=0;
	int sum_b=0;
	vector<int> va;
	vector<int> vb;

	
	for(int i=0; i<a.get_c_bloques(); i++){
		sum_a += a.get_bloque(i).get_tamano();
		va.push_back(sum_a);
	}
	for(int i=0; i<b.get_c_bloques(); i++){
		sum_b += b.get_bloque(i).get_tamano();
		vb.push_back(sum_b);
	}

	for(int i=0; i<va.size()-1; i++){
		for(int j=0; j<vb.size()-1; j++){
			if(va[i]==vb[j]){
				return false; 
			}
		}
	}
	return true;
}


void muro_t::write(ostream& os) const{
	for(int i=0; i<alto_; i++){
   		os << muro_[i] << endl;
	}
	
	//cout << time << endl;
}

ostream& operator<<(ostream& os, const muro_t& muro){
	muro.write(os);
	return os;
}















