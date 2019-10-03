#include "estado_t.hpp"
#include <utility>

using namespace std;

estado_t::estado_t(){
}

estado_t::~estado_t(){}

void estado_t::set_identificador(unsigned x){
    identificador_ = x;
}

unsigned estado_t::get_identificador(){
    return identificador_;
}

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
    //cout << transicion_out_[0].second;
    for(unsigned i=1; i<transiciones_; i++){
        if (m == transicion_out_[i].second){
            igual++;
        }
    }

    if(igual==transiciones_){
        if(identificador_ == transicion_out_[0].second)
            return true;
        else return false;
    }
    else return false;
}

bool estado_t::if_importante(){

    int p=0;
    importante_=false;
    
    if(if_aceptacion()==1){
        importante_=true;
    }

    for(int i=0; i<transiciones_; i++){
        if (get_second(i) != '&'){
            p++;
        }
    }
    if(p = transiciones_){
        importante_=true;
    }

    return importante_;
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
    return get<0>(transicion_out_[j]);
    //return transicion_out_[j].first;
}

unsigned estado_t::get_second(unsigned j){
    return get<1>(transicion_out_[j]);
    //return transicion_out_[j].second;
}


void estado_t::set_c_transicion(int t){
    transiciones_=t;
}

int estado_t::get_c_transicion(){
    return transiciones_;
}

void estado_t::write_transiciones(){
    for(int i=0; i<get_c_transicion(); i++){
        cout << transicion_out_[i].first << " " << transicion_out_[i].second << " ";
    }
    //cout << endl;
}


int estado_t::operator<(const estado_t &rhs) const{
    if(this-> identificador_ < rhs.identificador_)
		return 1;
	return 0;
}