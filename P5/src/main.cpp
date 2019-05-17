#include "language_t.hpp"
#include <string>
#include <iostream>


using namespace std;

int main(void){

	language_t L;
	int opcion;
	

do{

	cout << "________________________________________ " << endl;
	cout << "	<<MENU>> "<<endl;
	cout << "________________________________________" << endl << endl;
	cout << "			1.Inversa " << endl;
	cout << "			2.Concatenacion" << endl;
	cout << "			3.Union" << endl;
	cout << "			4.Interseccion" << endl;  
	cout << "			5.Diferencia" << endl;   
	cout << "			6.Sublenguaje" << endl;  
	cout << "			7.Igualdad de lenguajes" << endl;
	cout << "			8.Potencia"<< endl;
	cout << "			9.Cierre de Kleene" << endl; 
	cout << "			10.Salir" << endl;
	cout << "________________________________________" << endl;
	cout << "	>>>	Introduzca una opcion: ";    
    cin >> opcion;
    cout << endl << endl;


		switch(opcion){
			case 1:
				cout << "[INVERSA]: " << endl << "{";
				L.inversa();
				cout << "}" << endl;
			break;

			case 2:
				cout << "[CONCATENACION]" << endl << "{";
				L.concatenacion();
				cout << "}" << endl;
			break;

			case 3:
				cout <<"[UNION]" << endl <<"{";
				L.f_union();
				cout << "}" << endl;
			break;
				
			case 4:
				cout << "[INTERSECCION]:" << endl << "{";
				L.interseccion();
				cout << "}" << endl;
			break;
				
			case 5:
				cout << "[DIFERENCIA]:" << endl << "{";
				L.diferencia();
				cout << "}" << endl;
			break;
				
			case 6:
				cout << "[SUBLENGUAJE]: ";
				L.sublenguaje();
				cout << endl;
			break;
				
			case 7:
				cout << "[IGUALDAD DE LENGUAJES]: ";
				L.igualdad_lenguajes();
				cout << endl;
			break;
				
			case 8:
				int potencia;
				cout << "Introduzca exponente: ";
				cin >> potencia;
				cout << "[POTENCIA]: " << endl << "{";
				L.potencia(potencia);
				cout << "}" << endl;
			break;
			
			case 9:
				cout << "[CIERRE DE KLEENE]: " << endl << "{";
				L.cierre_kleene();
				cout << " ...}" << endl;
			break;
			
			case 10:
			
			cout << "Saliendo..." << endl << "Gracias por su visita :)" << endl;
				
			break;
				
			default:
			cout << "Esa opcion no es valida." << endl;
				
		}	
} while (opcion !=10 );
	
}
