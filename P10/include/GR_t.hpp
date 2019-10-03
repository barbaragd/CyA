#pragma once

#include <set>
#include <string>
#include "dfa_t.hpp"
#include <iterator>

/**
 * @brief Clase Grammar. Contiene el conjunto de símbolos, es decir, el alfabeto
 * el conjunto de símbolos no terminales,
 * el símbolo de arranque,
 * y el conjunto de reglas de sustitución.
 * 
 */
class GR_t{
    private:
        set<char> alfabeto_;        // conjunto de símbolos terminales
        set<char> v_;               // conjunto de símbolos no terminales
        char S_='S';                // símbolo de arranque (no terminal)
        vector<pair<char, vector<vector<char>>>>  P_;   // conjunto de reglas de sustitución

    public:
        GR_t(DFA_t dfa);
        GR_t(char nombre[]);
        ~GR_t();
        void exportar_gr(char nombrefichero[]);


        void eliminar_prod_vacias();
        void eliminar_prod_unitarias();

    private:
        bool prod_repetida(int i, vector<char> p);
        char get_next(set<pair<char,char>>& H, char a, int& flag);
        void insertar_prod(char x, pair<char, vector<vector<char>>>& pr, int no_ter);
        vector<vector<char>> borrar_prod(int e, vector<vector<char>> P);

};