#pragma once
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>

using namespace std;
#include "../include/tupla_t.hpp"


/**
 * @brief Clase Turing Machine. 
 * 
 */
class TuringMachine_t{
    private:
        int num_estados;                    // numero de estados de la maquina
        int e_arranque;                     // entero que indica el estado de arranque
        int estado_aceptacion;              // estado de aceptación
        int num_t_uplas;                    // entero indicando el número de t-uplas que componen la máquina
        vector<tupla_t> t_uplas;             // t-uplas de cada estado

        string cinta;


    public:
        TuringMachine_t(char nombrefichero1 [], char nombrefichero2 [], bool& error);
        ~TuringMachine_t();

        void show_turing_machine();
        bool simular_mt();


    private:
        void show_recorrido(string& tmp, unsigned pos, int e_act);
        int lookfor_transicion(char ent, int id); 
};