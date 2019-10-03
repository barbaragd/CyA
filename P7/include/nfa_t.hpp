#pragma once

#include <vector>
#include <set>
#include <string>
#include "estado_t.hpp"
#include <iterator>

using namespace std;

class NFA_t{
    private:
        set<estado_t> estados_;
        int num_est_;
        unsigned e_arranque_;
        int c=0;
	int a=0;

    public:
        NFA_t(char nombrefichero[], int &errorapertura, int &error_e_arranque);
        ~NFA_t();

        void show_nfa();
        void estados_muerte();
        void estados_importante();
        void es_dfa();

        void leer_cadena(string cadena);
        void leer_rec(string& cadena, vector<unsigned> est, unsigned id, int tam);

        void write_caminos(string cadena, vector<unsigned> est);

        
};
