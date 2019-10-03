#include <iostream>
#include "nfa_t.hpp"
#include <string>

using namespace std;

int main(){
    char nombrefichero[20];
    int errorapertura=0;
    int error_e_arranque=0;
    int error_no_dfa=0;
    int opcion;
    string cadena;

    cout << "Introduzca el fichero a usar: ";
    cin >> nombrefichero;
    cout << endl;

    NFA_t automata(nombrefichero, errorapertura, error_e_arranque);

    // ERRORES
    if(errorapertura==1){
        cout << "ERROR. Archivo no válido." << endl;
        return 0;
    }
    if(error_e_arranque==1){
        cout << "ERROR. Hay más de un estado de arranque." << endl;
    }


    do{
        cout << "-----------------------------" << endl;
        cout << " **[MENÚ]** " << endl;
        cout << " 1. Mostrar NFA" << endl;
        cout << " 2. Mostrar estados de muerte" << endl;
        cout << " 3. Mostrar estados importantes" << endl;
        cout << " 4. Mostrar si es un DFA" << endl;
        cout << " 5. Leer una cadena" << endl;
        cout << " 0. Salir" << endl;
        cout << "-----------------------------" << endl;
        cout << " Introduzca una opción: ";
        cin >> opcion;
        cout << "-----------------------------" << endl;
        cout << endl;

        switch(opcion){
            case 1:
                automata.show_nfa();
                cout << endl;
                break;
            case 2:
                automata.estados_muerte();
                cout << endl;
                break;
            case 3:
                automata.estados_importante();
                cout << endl;
                break;
            case 4:
                automata.es_dfa();
                cout << endl;
                break;
            case 5:
                cout << "Cadena de entrada: ";
                cin >> cadena;
                cout << endl;
                automata.leer_cadena(cadena);
                break;
           
            case 0:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida" << endl;
                //break;

        }


    }while(opcion != 0);
}
