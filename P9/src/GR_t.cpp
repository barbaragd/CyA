#include "../include/GR_t.hpp"
#include <fstream>
#include <iostream>
/**
 * @brief Construct a new gr t::gr t object
 * 
 * @param dfa 
 */
GR_t::GR_t(DFA_t dfa){
    // establecer sigman (alfabeto, símbolos terminales)
    alfabeto_ = dfa.get_alfabeto();

    // asignar a cada identificador una letra mayúscula (símbolo no terminal)
    vector<pair<unsigned, char>> simbolos; 

    // Estado S , el estado inicial
    pair<unsigned, char> s(0, 'S');
    simbolos.push_back(s);
    v_.insert('S');
    
    // Establecer el conjunto de símbolos no terminales
    char x='A';
    for(unsigned i=1; i<dfa.get_c_estados(); i++){
        v_.insert(x);
        pair<unsigned, char> aux(i,x);
        simbolos.push_back(aux);
        x++;
    }
    
    // reglas de producción
    P_.resize(dfa.get_c_estados());
    unsigned ids;
    char t;
    char nt;
    for(int i=0; i<dfa.get_c_estados(); i++){
        estado_t aux = dfa.get_estado(i);
        for(set<char>::iterator al=alfabeto_.begin(); al!=alfabeto_.end(); al++){
            t = *al;
            ids = aux.get_next(t);
            for(int j=0; j<simbolos.size(); j++){
                if(ids == simbolos[j].first){
                    nt = simbolos[j].second;
                }
            }
            P_[i].push_back(t); 
            P_[i].push_back(nt); ;
            P_[i].push_back('|'); 
        }
        if(aux.if_aceptacion()==true){
            P_[i].push_back('~');
        }
    }

}

/**
 * @brief Destroy the gr t::gr t object
 * 
 */
GR_t::~GR_t(){
    alfabeto_.clear();
    v_.clear();
    P_.clear();
}

/**
 * @brief Exportar la gramática, se le pasa el nombre del fichero 
 * donse se va a exportar.
 * 
 * @param nombrefichero 
 */
void GR_t::exportar_gr(char nombrefichero[]){
    ofstream sal(nombrefichero);

    // número total de símbolos terminales que posee la gramática.
    sal << alfabeto_.size() << endl;

    // lista de todos los símbolos terminales de la gramática
    for(set<char>::iterator al=alfabeto_.begin(); al!=alfabeto_.end(); al++){
        sal << (*al) << " ";
    }
    sal << endl;


    // número total de símbolos no terminales que posee la gramática
    sal << v_.size() << endl;

    // lista de todos los símbolos no terminales de la gramática
    for(set<char>::iterator i=v_.begin(); i!=v_.end(); i++){
        sal << (*i) << " ";
    }
    sal << endl;

    // reglas de producción del inicial
    int k = 0;
    set<char>::iterator it;
    it = v_.find('S');
    sal << (*it) << "->";    

    for(int i=0; i<P_[k].size(); i++){
        sal << P_[k][i];
    }
    sal << endl;
    set<char>::iterator j = v_.find('S');
    v_.erase(j);

    // reglas de producción 
    k = 1;
    int c=1;
    int cc=v_.size();
    set<char>::iterator i;
    for(i=v_.begin(); i!=v_.end(); i++){
        sal << (*i) << "->";
        for(int i=0; i<P_[k].size(); i++){
            sal << P_[k][i];
        }
        k++;
        sal << endl;
    }
    sal.close();
}