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

        int transiciones_;
        vector<pair<char, unsigned>> transicion_out_;

    public:
        estado_t(unsigned iden);
        estado_t();
        ~estado_t();

        void set_identificador(unsigned x);
        unsigned get_identificador();
        
        void set_aceptacion(bool x);//
        bool if_aceptacion(); //
        
        void set_inicial(bool x);//

        bool if_e_muerte();//

        void set_transiciones(char x, unsigned q);//
        void set_transiciones(pair<char,unsigned> aux);
        pair<char, unsigned> get_transiciones(unsigned j);
        bool comprobar_transiciones();//

        
        void write_transiciones();
        char get_first(unsigned j);//
        unsigned get_second(unsigned j);//
        unsigned get_next(char x);
        


        void set_c_transicion(int x);//
        int get_c_transicion();//

        int operator<(const estado_t &a)const;
        int operator==(const estado_t &a) const;
};
