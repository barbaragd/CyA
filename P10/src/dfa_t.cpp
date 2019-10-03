#include "../include/dfa_t.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <iterator>

using namespace std;

/**
 * @brief Establcer el estado de arranque
 * 
 */
void DFA_t::set_earranque(unsigned x){
    e_arranque_ = x;
}

/**
 * @brief Retornar el estado de arranque
 * 
 * @return unsigned 
 */
unsigned DFA_t::get_earranque(){
    return e_arranque_;
}


/**
 * @brief Retornar el alfabeto.
 * 
 * @return set<char> 
 */
set<char> DFA_t::get_alfabeto(){
    return alfabeto_;
}


/**
 * @brief Obtener la cantidad de estados.
 * 
 * @return int 
 */
int DFA_t::get_c_estados(){
    return estados_.size();
}


/**
 * @brief Obtener un estado por medio de su identificador
 * 
 * @param id 
 * @return estado_t 
 */
estado_t DFA_t::get_estado(unsigned id){
    set<estado_t>::iterator it;
    estado_t aux;
    for(it=estados_.begin(); it!=estados_.end(); it++){
        aux = *it;
        if(aux.get_identificador() == id){
            return aux;
        }
    }
}

/**
 * @brief Construct a new dfa t::dfa t object
 * 
 * @param nombrefichero 
 * @param errorapertura 
 * @param error_e_arranque 
 * @param error_no_dfa 
 */
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
            // ESTABLECER ESTADO DE ARRANQUE
            set_earranque(x);
          
            // LEER LAS TRANSICIONES
            int fin=1;
            while(fin <= e){
                Aut >> id >> acep >> tran;
                estado_t aux;
                //cout << id << " " << acep << " " << tran << " ";
                aux.set_identificador(id);                
                aux.set_aceptacion(acep);
                aux.set_c_transicion(tran);

                for(int i=0; i<aux.get_c_transicion(); i++){
                    Aut >> t >> ids;
                    alfabeto_.insert(t);
                    aux.set_transiciones(t, ids);   
                }
                fin++;
                if(aux.comprobar_transiciones()==false){
                    error_no_dfa = 1;
                }
                estados_.insert(aux);
            }   
        }
    }
    else {
        errorapertura=1;
    }
}

//DFA_t::DFA_t(){}

/**
 * @brief Destroy the dfa t::dfa t object
 * 
 */
DFA_t::~DFA_t(){}

/**
 * @brief Mostrar el DFA por pantalla en el mismo formato en el que ha sido
 * introducido por el fichero.
 * 
 */
void DFA_t::show_dfa(){
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


/**
 * @brief Indicar los estados de muerte y mostrar cuántos son.
 * 
 */
void DFA_t::estados_muerte(){
    int m=0;
    set<estado_t>::iterator it;
    estado_t aux;
    for(it=estados_.begin(); it!=estados_.end(); it++){
        aux = *it;
        //cout << aux.get_identificador() << endl;
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
                cout << aux.get_identificador() << ",";
            }
        }
    cout << endl;
    }
    else {
        cout << "No hay estados de muerte." << endl;
    }
}

/**
 * @brief Se le pasa la cadena que se quiere 
 * comprobar si pertenece al DFA. 
 * 
 * @param cadena 
 */
void DFA_t::leer_cadena(string cadena){
    set<estado_t>::iterator it;
    estado_t aux;
    unsigned id = e_arranque_;

    vector<unsigned> est;

    leer_rec(cadena, est, id, 0);


}
/**
 * @brief Recurisvo. Se pasa la cadena, el vector de estados recorridos, el identificador
 * del último estado, y el tamaño de la cadena que se ha leído.
 * 
 * @param cadena 
 * @param est 
 * @param id 
 * @param tam 
 */
void DFA_t::leer_rec(string cadena, vector<unsigned> est, unsigned id, int tam){
    if(est.size() == cadena.size()){
        write(cadena, est);
        return;
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
                        return;
                    }
                }
            }
        }
    }

}


/**
 * @brief Mostrar la lectura de la cadena. Se le pasa por parámetros la cadena, 
 * y el vector que contiene los estados recorridos
 * 
 * @param cadena 
 * @param est 
 */
void DFA_t::write(string cadena, vector<unsigned> est){
    cout << "Estado actual\tEntrada\t\tEstado Siguiente" << endl;
    cout << e_arranque_ << "\t\t" << cadena[0] << "\t\t" << est[0] << endl;
    for(int i=1; i<cadena.size(); i++){
        cout <<  est[i-1]<< "\t\t" << cadena[i] << "\t\t" << est[i] << endl;
    }

    estado_t aux;
    set<estado_t>::iterator it;
    unsigned x = est[est.size()-1];
    for(it=estados_.begin(); it!=estados_.end(); it++){
        aux = *it;
        if(aux.get_identificador() == x){
            if(aux.if_aceptacion()==true){
                cout << "Cadena aceptada" << endl;
            }
            else 
                cout << "Cadena NO aceptada" << endl;
        }
    }
    cout << endl;
}