#include "../include/estado_t.hpp"
#include <utility>

using namespace std;

/**
 * @brief Construct a new estado t::estado t object
 * 
 */
estado_t::estado_t(){
}

// estado_t::estado_t(unsigned iden): identificador_(iden){
// }

/**
 * @brief Destroy the estado t::estado t object
 * 
 */
estado_t::~estado_t(){}

/**
 * @brief Establece el identicador.
 * 
 * @param x 
 */
void estado_t::set_identificador(unsigned x){
    identificador_ = x;
}

/**
 * @brief Retonar el identificador del estado
 * 
 * @return unsigned 
 */
unsigned estado_t::get_identificador(){
    return identificador_;
}

/**
 * @brief Establecer si el estado es de aceptación o no.
 * 
 * @param x 
 */
void estado_t::set_aceptacion(bool x){
    aceptacion_ = x;
}

/**
 * @brief Retorna si el estado es de aceptación o no. 
 * 
 * @return true 
 * @return false 
 */
bool estado_t::if_aceptacion(){
    return aceptacion_;
}

/**
 * @brief Establecer si es el estado inicial.
 * 
 * @param x 
 */
void estado_t::set_inicial(bool x){
    inicial_ = x;
}

/**
 * @brief Mostrar si es estado de muerte o no.
 * 
 * @return true 
 * @return false 
 */
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

/**
 * @brief Establecer las transiciones, se le pasa el 
 * parámetro "x" que va hacia el estado "q"
 * 
 * @param x 
 * @param q 
 */
void estado_t::set_transiciones(char x, unsigned q){
    pair<char, unsigned> aux(x,q);
    transicion_out_.push_back(aux);
}

/**
 * @brief Lo mismo que el anterior pero mandando ya el pair con
 * el parámetro "x" y el estado hacia el que se transita. 
 * 
 * @param aux 
 */
void estado_t::set_transiciones(pair<char,unsigned> aux){
    transicion_out_.push_back(aux);
}

/**
 * @brief Comprobar que el número de transiciones coincide con 
 * el número de letras del alfabeto, es decir, que sea un DFA
 * 
 * @return true 
 * @return false 
 */
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

/**
 * @brief Retorna el símbolo del alfabeto con el que se hace 
 * la transición número j
 * 
 * @param j 
 * @return char 
 */
char estado_t::get_first(unsigned j){
    return get<0>(transicion_out_[j]);
    //return transicion_out_[j].first;
}

/**
 * @brief Se retorna el estado al que se llega en la 
 * transición número j
 * 
 * @param j 
 * @return unsigned 
 */
unsigned estado_t::get_second(unsigned j){
    return get<1>(transicion_out_[j]);
    //return transicion_out_[j].second;
}

/**
 * @brief Con el símbolo "x" se retorna el estado al 
 * que se transita.
 * 
 * @param x 
 * @return unsigned 
 */
unsigned estado_t::get_next(char x){
	for (int i=0; i<transiciones_; i++){
		if(get_first(i)==x){
			return get_second(i);
		}
	}
	return -1;
}

/**
 * @brief Establecer el número de transiciones
 * 
 * @param t 
 */
void estado_t::set_c_transicion(int t){
    transiciones_=t;
}

/**
 * @brief Retornar el número de transiciones
 * 
 * @return int 
 */
int estado_t::get_c_transicion(){
    return transiciones_;
}

/**
 * @brief Retornar la transición número j
 * 
 * @param j 
 * @return pair<char, unsigned> 
 */
pair<char, unsigned> estado_t::get_transiciones(unsigned j){
    return transicion_out_[j];
}

/**
 * @brief Escribir las transiciones del estado.
 * 
 */
void estado_t::write_transiciones(){
    for(int i=0; i<get_c_transicion(); i++){
        cout << transicion_out_[i].first << " " << transicion_out_[i].second << " ";
    }
}

/**
 * @brief Sobrecarga del operador < para ordenar los estado 
 * por el identificador.
 * 
 * @param a 
 * @return int 
 */
int estado_t::operator<(const estado_t &a) const{
    if(this-> identificador_ < a.identificador_)
		return 1;
	return 0;
}

/**
 * @brief Ver si dos estados son iguales por su identificador.
 * 
 * @param a 
 * @return int 
 */
int estado_t::operator==(const estado_t &a) const{
    if (identificador_ == a.identificador_)
        return 1;
    return 0;
}