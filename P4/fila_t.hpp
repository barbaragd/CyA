#pragma once

#include "bloque_t.hpp"
#include <vector>
#include <iostream>

using namespace std;

class fila_t{
	private:
		vector<bloque_t> fila_;
		int tam_max_;
		int tam_act_;
		int c_bloques;
	
	public:
		fila_t(int t_m);
		~fila_t(){}
		
		void meter_bloque(bloque_t bloque);
		void sacar_bloque();	
		
		void write(ostream& os) const;
		
		int get_tam_max_();
		int get_tam_act_();
		int get_c_bloques(); //tamaño del vector de bloques
		
		bloque_t get_bloque(int pos);
};

ostream& operator<<(ostream& os, const fila_t& fila);
