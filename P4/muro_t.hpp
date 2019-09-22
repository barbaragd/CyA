#pragma once

//#include "bloque_t.hpp"
#include "fila_t.hpp"
#include <vector>
#include <iostream>

using namespace std;

class muro_t{
	private:
		vector<fila_t>	muro_;
		int ancho_;
		int alto_;
		int altura_actual_;
		
		
	public:
		muro_t(int ancho, int alto);
		~muro_t(){}
		
		int get_ancho();
		int get_alto();
		int get_altura_actual();
		fila_t get_fila(int pos);
		
		int get_c_bloques();
		
		void meter_fila(fila_t fila);
		void sacar_fila();
		
		bool comparar_filas(fila_t una, fila_t dos);

		void write(ostream& os) const;
};

ostream& operator<<(ostream& os, const muro_t& muro);
