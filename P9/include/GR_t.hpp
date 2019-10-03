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
        set<char> alfabeto_;        // sigma
        set<char> v_;               // conjunto de símbolos no terminales
        char S_='S';                // símbolo de arranque (no terminal)
        vector<vector<char>>  P_;   // conjunto de reglas de sustitución

    public:
        GR_t(DFA_t dfa);
        ~GR_t();
        void exportar_gr(char nombrefichero[]);

};