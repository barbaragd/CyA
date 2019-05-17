#include "dfa_t.hpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

DFA_t::DFA_t(char nombrefichero[], int &errorapertura, int &error_e_arranque, int &error_no_dfa){
    ifstream Aut(nombrefichero);
    int e, acep, tran;
    unsigned id, ids, x;
    char t;
    string leer;


    if(Aut.is_open()){
        Aut >> e;
        getline(Aut, leer);
        if(!leer.empty()){
            cout << "Error en la primera línea. Se tomará el primer valor leído." << endl;
        }

        Aut >> x;
        leer.erase();
        getline(Aut, leer); 

        if(!leer.empty()){
            error_e_arranque = 1;
        }

        else{ 
            estados_.resize(e); // vector de estados con todos los estados
            e_arranque_ = x;

            for(int i=0; i<e; i++){
                estados_[i].set_inicial(false); 
            }
            estados_[e_arranque_].set_inicial(true); // sólo establezco uno como arranque

            int fin=1;
            while(fin <= e){
                Aut >> id >> acep >> tran;             
                estados_[id].set_aceptacion(acep);
                estados_[id].set_c_transicion(tran);
                for(int i=0; i<estados_[id].get_c_transicion(); i++){
                    Aut >> t >> ids;
                    estados_[id].set_transiciones(t, ids);
                }
                fin++;
                if(estados_[id].comprobar_transiciones()==false){
                    error_no_dfa = 1;
                }
            }
        }
    }
    else {
        errorapertura=1;
    }
}

DFA_t::~DFA_t(){}

void DFA_t::show_dfa(){
    cout << estados_.size() << endl << e_arranque_ << endl;
    for(unsigned i=0; i<estados_.size(); i++){
        cout << i << " ";
        cout << estados_[i].if_aceptacion() << " ";
        cout << estados_[i].get_c_transicion() << " ";
        for(unsigned j=0; j<estados_[i].get_c_transicion(); j++){
            cout << estados_[i].get_first(j) << " " << estados_[i].get_second(j) << " ";
        }
        cout << endl;
    }
}


// indicar cuantos estados de muerte y cuáles son
void DFA_t::estados_muerte(){
    int m=0;

    for(int i=0; i<estados_.size(); i++){
        if(estados_[i].if_e_muerte()){
            m++;
        }
    }
    
    if(m!=0){
        cout << "Hay " << m << " estado(s) de muerte" << endl;
        cout << "El/Los estado(s) de muerte es/son: ";
        for(int i=0; i<estados_.size(); i++){
            if(estados_[i].if_e_muerte()){
                cout << i << ",";
            }
        }
    cout << endl;
    }
    else {
        cout << "No hay estados de muerte." << endl;
    }
}

bool DFA_t::leer_cadena(string cadena){
    unsigned id = e_arranque_;
    int i=0;
    int no=0;
    
    while(i<cadena.length()){
        no = 0;
        cout << "Estado actual: "; 
        cout << id << endl;
        for(int j=0; j<estados_[id].get_c_transicion(); j++){
            if(cadena.at(i) == estados_[id].get_first(j)){
                cout << "Entrada: " << cadena.at(i) << endl;
                id = estados_[id].get_second(j);
                cout << "Estado siguiente: " << id << endl;
                j = estados_[id].get_c_transicion(); // no quiero recorrer las demas posibles transiciones.
            }
            else no++;
        }
        cout << endl;
        if(no == estados_[id].get_c_transicion())
           return false;
        i++;
    }
    if(estados_[id].if_aceptacion()) return true;
    else return false;
}
