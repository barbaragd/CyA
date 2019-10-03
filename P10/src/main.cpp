#include <iostream>
#include "../include/GR_t.hpp"
#include <string>

using namespace std;

int main(int argc, char *argv[]){
    if(argc > 3 || argc < 3){
        cout << "Error en la introducción de los ficheros" << endl;
        return -1;
    }
    
    GR_t gramatica(argv[1]);
    gramatica.eliminar_prod_vacias();
    gramatica.eliminar_prod_unitarias();
    gramatica.exportar_gr(argv[2]);

}