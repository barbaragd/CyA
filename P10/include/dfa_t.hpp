#pragma once

#include <vector>
#include <set>
#include <string>
#include "estado_t.hpp"
#include <iterator>

using namespace std;

/**
 * @brief Clase DFA que contiene un conjunto de estados, 
 * el estado de arranque, el conjutno de alfabeto, y la
 * cantidad de estados.
 * 
 */
class DFA_t{
    private:
        set<estado_t> estados_;
        unsigned e_arranque_;
        set<char> alfabeto_;
        int c_estados_;
        

    public:
        DFA_t(char nombrefichero[], int &errorapertura, int &error_e_arranque, int &error_no_dfa);
        //DFA_t();
        ~DFA_t();

        void set_earranque(unsigned x);
        unsigned get_earranque();

        set<char> get_alfabeto();//new
        estado_t get_estado(unsigned id);//new
        int get_c_estados();//new

        void show_dfa();//
        void estados_muerte();//

        void leer_cadena(string cadena);//
        void leer_rec(string cadena, vector<unsigned> est, unsigned id, int tam);//

        void write(string cadena, vector<unsigned> est);//

        
};