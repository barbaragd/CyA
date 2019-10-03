/**
 * @file estado_t.hpp
 * @Barbara {Barbara} (alu0101108452@ull.edu.es})
 * @brief 
 * @version 0.1
 * @date 2018-12-17
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#pragma once

#include <vector>
#include <iostream>
#include <utility>


using namespace std;

/**
 * @brief Clase estado 
 * Contiene el identificador, si es de aceptación,
 * si es el estado inicial, y si es un estado de muerte  
 */

class estado_t{
    private:
        unsigned identificador_;
        bool aceptacion_;
        bool inicial_;
        bool e_muerte_;

        int transiciones_;
        vector<pair<char, unsigned>> transicion_out_;

    public:
        estado_t();
        ~estado_t();

        void set_identificador(unsigned x);
        unsigned get_identificador();
        
        void set_aceptacion(bool x);
        bool if_aceptacion(); 
       
        void set_inicial(bool x);

        bool if_e_muerte();

        void set_transiciones(char x, unsigned q);
        void set_transiciones(pair<char,unsigned> aux);
        pair<char, unsigned> get_transiciones(unsigned j);
        bool comprobar_transiciones();

        
        void write_transiciones();
        char get_first(unsigned j);
        unsigned get_second(unsigned j);
        unsigned get_next(char x);
        


        void set_c_transicion(int x);//
        int get_c_transicion();//

        int operator<(const estado_t &a)const;
        int operator==(const estado_t &a) const;
};
