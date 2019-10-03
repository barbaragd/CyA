#include "nfa_t.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <iterator>

using namespace std;

NFA_t::NFA_t(char nombrefichero[], int &errorapertura, int &error_e_arranque){
    ifstream Aut(nombrefichero);
    int e, acep, tran;
    unsigned id, ids, x;
    char t;
    string leer;


    if(Aut.is_open()){
        Aut >> e;
        num_est_ = e;
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
            // ESTABLECER ESTADO DE ARRANQUE
            e_arranque_ = x;
          
            // LEER LAS TRANSICIONES
            int fin=1;
            while(fin <= e){
                Aut >> id >> acep >> tran;
                estado_t aux;
                aux.set_identificador(id);                
                aux.set_aceptacion(acep);
                aux.set_c_transicion(tran);

                for(int i=0; i<aux.get_c_transicion(); i++){
                    Aut >> t >> ids;
                    aux.set_transiciones(t, ids);   
                }
                fin++;
                estados_.insert(aux);
            }   
        }
    }
    else {
        errorapertura=1;
    }
}

NFA_t::~NFA_t(){}

void NFA_t::show_nfa(){
    set<estado_t>::iterator it;
    cout << estados_.size() << endl << e_arranque_ << endl;
    unsigned i=0;
    estado_t aux;
    for(it=estados_.begin(); it!=estados_.end(); it++){
        aux = *it;
        cout << aux.get_identificador() << " ";
        cout << aux.if_aceptacion() << " ";
        cout << aux.get_c_transicion() << " ";
        aux.write_transiciones();
        cout << endl;
    }
}


// indicar cuantos estados de muerte y cuáles son
void NFA_t::estados_muerte(){
    int m=0;
    set<estado_t>::iterator it;
    estado_t aux;
    for(it=estados_.begin(); it!=estados_.end(); it++){
        aux = *it;
        if(aux.if_e_muerte()){
            m++;
        }
    }
    
    if(m!=0){
        cout << "Hay " << m << " estado(s) de muerte" << endl;
        cout << "El/Los estado(s) de muerte es/son: ";
        for(it=estados_.begin(); it!=estados_.end(); it++){
            aux = *it;
            if(aux.if_e_muerte()){
                cout << "[" << aux.get_identificador() << "],";
            }
        }
    }
    else {
        cout << "No hay estados de muerte." << endl;
    }
}


void NFA_t::estados_importante(){
    set<estado_t>::iterator it;
    estado_t aux;
    set<estado_t> importantes;
    set<estado_t> no_importantes;

    for(it=estados_.begin(); it!=estados_.end(); it++){
        aux = *it;
        if (aux.if_importante()){
            importantes.insert(aux);
        }
        else no_importantes.insert(aux);
    }

    if(importantes.empty()){
        cout << "No hay estados importantes" << endl;
    }
    else{
        cout << "Los estados importantes son: ";
        for(it=importantes.begin(); it!=importantes.end(); it++){
            aux = *it;
            cout << aux.get_identificador() << ",";
        }
    }
    cout << endl << endl;
    
    if(no_importantes.empty()){
        cout << "No hay estados NO importantes" << endl;
    }
    else{
        cout << "Los estados NO importantes son: ";
        for(it=no_importantes.begin(); it!=no_importantes.end(); it++){
            aux = *it;
            cout << aux.get_identificador() << ",";
        }
    }
 
}

//comprobar si es dfa
void NFA_t::es_dfa(){
    set<estado_t>::iterator it;
    estado_t aux;
    int w=0;
    for(it=estados_.begin(); it!=estados_.end(); it++){
        aux = *it;
        if(aux.comprobar_transiciones()==false){
            w++;
        }
    }
    if(w==num_est_){
        cout << "Es un DFA" << endl;
    }
    else {
        cout << "NO es un DFA" << endl;
    }
}



//leer cadena
void NFA_t::leer_cadena(string cadena){
    set<estado_t>::iterator it;
    estado_t aux;
    unsigned id = e_arranque_;

    vector<unsigned> est;

    leer_rec(cadena, est, id, 0);

    if(c==0){
        cout << "Cadena NO aceptada" << endl;
    }
    c=0;
    cout << endl;
	
	cout << "Decisión final: " << endl;
	if (a==1){
		cout << "Cadena aceptada" << endl;
	}
	else
		cout << "Cadena NO aceptada" << endl;
	a=0;
}


void NFA_t::leer_rec(string& cadena, vector<unsigned> est, unsigned id, int tam){
    if(est.size() == cadena.size()){
        write_caminos(cadena, est);
    }
    else{
        set<estado_t>::iterator it=estados_.begin();
        estado_t aux;

        for(it=estados_.begin(); it!=estados_.end(); it++){
            aux = *it;
            if(aux.get_identificador()==id){
                for(int j=0; j<aux.get_c_transicion(); j++){
                    if(cadena[tam] == aux.get_first(j)){
                        id = aux.get_second(j);
                        est.push_back(id);
                        tam = est.size();

                        leer_rec(cadena, est, id, tam);

                        est.pop_back();
                        id = est[est.size()-1];
                        tam--;
                    }
                }
                for(int j=0; j<aux.get_c_transicion(); j++){
                    if(aux.get_first(j) == '&'){
                        id = aux.get_second(j);

                        leer_rec(cadena, est, id, tam);

                        est.pop_back();
                        tam--;                      
                    }
                }
            }
        }
    }
}


void NFA_t::write_caminos(string cadena, vector<unsigned> est){

    c++;

    cout << "Camino " << c << ":" << endl;

    cout << "Estado actual\tEntrada\t\tEstado siguiente" << endl;
    cout << e_arranque_ << "\t\t" << cadena[0] << "\t\t" << est[0] << endl;
    for(int i=1; i<est.size(); i++){
        cout << est[i-1]<< "\t\t"<< cadena[i] << "\t\t" << est[i];
        cout << endl;
    }


    estado_t aux;
    set<estado_t>::iterator it;
    unsigned x = est[est.size()-1];
    for(it=estados_.begin(); it!=estados_.end(); it++){
        aux = *it;
        if(aux.get_identificador() == x){
            if(aux.if_aceptacion()==true){
                cout << "Cadena aceptada" << endl;
				a=1;
            }
            else
                cout << "Cadena NO aceptada" << endl;

        }
    }

    cout << endl << endl;

}


