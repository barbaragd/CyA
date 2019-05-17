#pragma once
#include <vector>
#include <string>
#include "estado_t.hpp"

class DFA_t{
    private:
        vector<estado_t> estados_;
        unsigned e_arranque_;

    public:
        DFA_t(char nombrefichero[], int &errorapertura, int &error_e_arranque, int &error_no_dfa);
        ~DFA_t();

        void show_dfa();
        void estados_muerte();

        bool leer_cadena(string cadena);
        
};
