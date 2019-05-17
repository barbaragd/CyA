#include "estado_t.hpp"
#include <utility>

using namespace std;

estado_t::estado_t(){
}

estado_t::~estado_t(){}

void estado_t::set_aceptacion(bool x){
    aceptacion_ = x;
}

bool estado_t::if_aceptacion(){
    return aceptacion_;
}

void estado_t::set_inicial(bool x){
    inicial_ = x;
}

bool estado_t::if_e_muerte(){
    int igual=1;
    

    unsigned m=transicion_out_[0].second;
    for(unsigned i=1; i<transiciones_; i++){
        if (m == transicion_out_[i].second){
            igual++;
        }
    }
    if(igual==transiciones_){
        return true;
    }
    else return false;
}

void estado_t::set_transiciones(char x, unsigned q){
    pair<char, unsigned> aux(x,q);
    transicion_out_.push_back(aux);
}

bool estado_t::comprobar_transiciones(){
    char igual;
    for(unsigned i=0; i<transiciones_; i++){
        igual=transicion_out_[i].first;
        for(unsigned j=0; j<transiciones_; j++){
            if((i!=j) && (igual==transicion_out_[j].first)){
                return false;
            }
        }
    }
    return true;
}

char estado_t::get_first(unsigned j){
    return transicion_out_[j].first;
}

unsigned estado_t::get_second(unsigned j){
    return transicion_out_[j].second;
}


void estado_t::set_c_transicion(int t){
    transiciones_=t;
}

int estado_t::get_c_transicion(){
    return transiciones_;
}