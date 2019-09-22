#include "muroconstruido_t.hpp"

#include <vector>
#include <iostream>


using namespace std;

int main(){
	cout << "------------------------CONSTRUCCIÓN DEL MURO------------------------" << endl;
	
	int ancho, alto;
	
	cout << "Introduzca el ancho del muro deseado: "; 
	cin >> ancho;
	
	cout << "Introduzca la altura del muro deseado: ";
	cin >> alto;
	cout << endl << endl;
	
	muroconstruido_t mimuro(ancho, alto);
	
	mimuro.mostrar_muros();
	mimuro.mostrar_filas();
	cout << endl;
	mimuro.mostrar_tiempo();
	
	cout << "----------------------------------------------------------------------" << endl;
	
}
