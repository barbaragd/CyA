#pragma once

#include <vector>
#include <iostream>
#include <utility>


using namespace std;

class estado_t{
    private:
        unsigned identificador_;
        bool aceptacion_;
        bool inicial_;
        bool e_muerte_;
        bool importante_;

        int transiciones_;
        vector<pair<char, unsigned>> transicion_out_;

    public:
        estado_t();
        ~estado_t();

        void set_identificador(unsigned x);
        unsigned get_identificador();
        
        void set_aceptacion(bool x);//
        bool if_aceptacion(); //
        
        void set_inicial(bool x);//

        bool if_e_muerte();//

        bool if_importante();


        void set_transiciones(char x, unsigned q);//
        bool comprobar_transiciones();//

        
        void write_transiciones();
        char get_first(unsigned j);//
        unsigned get_second(unsigned j);//
        
        void set_c_transicion(int x);//
        int get_c_transicion();//

        int operator<(const estado_t &a)const;
};
