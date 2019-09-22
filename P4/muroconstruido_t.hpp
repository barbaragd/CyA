#pragma once

#include "muro_t.hpp"

#include <vector>

class muroconstruido_t{

	private:
		vector<muro_t> todosmuros_;
		vector<fila_t> todasfilas_;
		
		double tiempo_muro;
		double tiempo_fila;
		
		
	public:
		muroconstruido_t(int ancho,int alto);
		~muroconstruido_t(){}

		void generar_filas(fila_t fila); 
		void building_muros(muro_t muro);
		
		void mostrar_muros();
		void mostrar_filas();
		void mostrar_tiempo();
};
