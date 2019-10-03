#include <iostream>
#include "../include/TuringMachine_t.hpp"
#include <string>


int main(int argc, char *argv[]){
    unsigned opcion;
    bool acep;
    bool error=false;
    
    if(argc > 3 || argc < 3){
        cout << "Error en la introducción de los ficheros" << endl;
        return -1;
    }
    
    TuringMachine_t maquinaturing(argv[1], argv[2], error);
    if(error==false){
        cout << " >> ¿Mostrar la máquina de turing por pantalla?" << endl;
        cout << "Sí (Pulsa 1)" << endl;
        cout << "No (Pulsa 0)" << endl << "Opción: ";
        cin >> opcion;
        cout << endl;
        if(opcion==1){
            maquinaturing.show_turing_machine();
        }

        acep = maquinaturing.simular_mt();
        cout << endl;
        if(acep){
            cout << "Cadena ACEPTADA" << endl;
        }
        else{
            cout << "Cadena NO ACEPTADA" << endl;
        }
    }
}
