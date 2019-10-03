#include <iostream>
#include "dfa_t.hpp"
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

    DFA_t automata(nombrefichero, errorapertura, error_e_arranque, error_no_dfa);
    DFA_t aut_b;

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



    do{
        cout << "-----------------------------" << endl;
        cout << " **[MENÚ]** " << endl;
        cout << " 1. Mostrar DFA" << endl;
        cout << " 2. Mostrar estados de muerte" << endl;
        cout << " 3. Leer una cadena" << endl;
        cout << " 4. Minimizar" << endl;
        cout << " 0. Salir" << endl;
        cout << "-----------------------------" << endl;
        cout << " Introduzca una opción: ";
        cin >> opcion;
        cout << "-----------------------------" << endl;
        cout << endl;

        switch(opcion){
            case 1:
                automata.show_dfa();
                cout << endl;
                break;
            case 2:
                automata.estados_muerte();
                cout << endl;
                break;
            case 3:
                cout << "Cadena de entrada: ";
                cin >> cadena;
                cout << endl;
                automata.leer_cadena(cadena);
                break;
            case 4:
                automata.minimize(aut_b);
                cout << endl;
                break;           
            case 0:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida" << endl;
        }
        
    }while(opcion != 0);
}
