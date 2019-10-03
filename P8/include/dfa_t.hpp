#pragma once

#include <vector>
#include <set>
#include <string>
#include "estado_t.hpp"
#include <iterator>

using namespace std;

class DFA_t{
    private:
        set<estado_t> estados_;
        unsigned e_arranque_;
        // estado_t e_arranque;
        set<char> alfabeto_;
        

    public:
        DFA_t(char nombrefichero[], int &errorapertura, int &error_e_arranque, int &error_no_dfa);
        DFA_t();
        ~DFA_t();

        void set_earranque(unsigned x);
        unsigned get_earranque();
        void show_dfa();
        void estados_muerte();

        void leer_cadena(string cadena);
        void leer_rec(string cadena, vector<unsigned> est, unsigned id, int tam);
        void write(string cadena, vector<unsigned> est);

        // Métodos de minimizar // Práctica 8
        void minimize(DFA_t& dfa_min);
        set<set<estado_t>> new_part(set<set<estado_t>>  PI_vieja, int& contador);
        set<set<estado_t>> descomponer(set<estado_t> conjunto, set<set<estado_t>>  PI_vieja, int& contador);
        set<set<estado_t>> part(set<estado_t> G, char simbolo, set<set<estado_t>> PI_vieja);
        void writePart(set<set<estado_t>>pariticion, int& contador, char s, set<estado_t> G, set<set<estado_t>> PI);
        
        void build_DFA(set<set<estado_t>> PI, unsigned e_arranque, int cont);
        void exportar_dfa();



        
};
