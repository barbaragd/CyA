#include <iostream>
#include "../include/GR_t.hpp"
#include <string>

using namespace std;

int main(int argc, char *argv[]){
	
	if(argc != 3){
		cout << "Falta un fichero" << endl;
		return 0;
	}

    int errorapertura=0;
    int error_e_arranque=0;
    int error_no_dfa=0;
    int opcion;
    string cadena;

    DFA_t automata(argv[1], errorapertura, error_e_arranque, error_no_dfa);

    // ERRORES
    if(errorapertura==1){
        cout << "ERROR. Archivo no válido." << endl;
        return 0;
    }
    if(error_no_dfa==1){
        cout << "ERROR. No es un autómata finito." << endl;
    }
    if(error_e_arranque==1){
        cout << "ERROR. Hay más de un estado de arranque." << endl;
    }
    if((error_no_dfa==1) || (error_e_arranque==1)){
        return 0;
    }

    GR_t gramatica(automata);

    gramatica.exportar_gr(argv[2]);

}
