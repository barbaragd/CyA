#include "muroconstruido_t.hpp"
#include <ctime>
#include <vector>


muroconstruido_t::muroconstruido_t(int ancho, int alto){
	unsigned t0_fila, t1_fila, t0_muro, t1_muro;
	
	t0_fila = clock();
	generar_filas(fila_t(ancho));
	t1_fila = clock();
	
	tiempo_fila = double(t1_fila - t0_fila) / CLOCKS_PER_SEC;
	
	
	t0_muro = clock();
	building_muros(muro_t(ancho, alto));
	t1_muro = clock();
	
	tiempo_muro = double(t1_muro - t0_muro) / CLOCKS_PER_SEC;
}



void muroconstruido_t::generar_filas(fila_t fila){
	// todas las filas posibles estan en el vector de vectores "todasfilas"
	if(fila.get_tam_act_() == fila.get_tam_max_()){
		todasfilas_.push_back(fila);
	}
	else if(fila.get_tam_act_() < fila.get_tam_max_()){
		fila.meter_bloque(bloque_t (2));
		generar_filas(fila);		
		
		fila.sacar_bloque();
		fila.meter_bloque(bloque_t (3));
		generar_filas(fila);
		
	}
}




void muroconstruido_t::building_muros(muro_t muro){	
	for(int i=0; i<todasfilas_.size(); i++){
	
		if(muro.get_altura_actual() == muro.get_alto()){
			todosmuros_.push_back(muro);
			return;
		}
		
		else if(muro.get_altura_actual() < muro.get_alto()){
			muro.meter_fila(todasfilas_[i]);
			if(muro.get_altura_actual() == 1){
				building_muros(muro);
			}
			else{
				fila_t una = muro.get_fila(muro.get_altura_actual() -1);						
				fila_t dos = muro.get_fila(muro.get_altura_actual() -2);
				if(muro.comparar_filas(dos, una)) {
					building_muros(muro);
				}
			}
		}
		
		muro.sacar_fila();
	}
}


void muroconstruido_t::mostrar_muros(){
	
	cout << "# Hay " << todosmuros_.size() << " muros posibles: " << endl;

	for(int i=0; i<todosmuros_.size(); i++){
		cout << "[Muro " << i+1 << "]:	" << endl;
		cout << todosmuros_[i] << endl;
		cout << "Cantidad de bloques empleados: " << todosmuros_[i].get_c_bloques() << endl << endl << endl;
	}
	cout << endl;

}

void muroconstruido_t::mostrar_filas(){

	cout << "# Hay " << todasfilas_.size() << " filas posibles: "<< endl;

	for(int i=0; i<todasfilas_.size(); i++){
		cout << "[Fila " << i+1 << "]: " << todasfilas_[i] << endl;
		cout << "Cantidad de bloques empleados: " << todasfilas_[i].get_c_bloques() << endl << endl;
	}
	cout << endl;

}

void muroconstruido_t::mostrar_tiempo(){
	cout << "# [Tiempo de ejecución]: " << endl;
	cout << "Tiempo requerido en generar las filas: " << tiempo_fila << endl;
	cout << "Tiempo requerido en la construcción de los muros: " << tiempo_muro << endl;
}
