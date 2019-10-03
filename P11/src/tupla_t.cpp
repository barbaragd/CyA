#include "../include/tupla_t.hpp"

using namespace std;
/**
 * @brief Construct a new tupla t::tupla t object
 * 
 */
tupla_t::tupla_t(){}

/**
 * @brief Construct a new tupla t::tupla t object
 * 
 * @param estado 
 * @param entrada 
 * @param escribe 
 * @param movimiento 
 * @param sig_estado 
 */
tupla_t::tupla_t(int estado, char entrada, char escribe, char movimiento, int sig_estado){
    build(estado, entrada, escribe, movimiento, sig_estado);
}

/**
 * @brief Establece los valores que la clase necesita.
 * 
 * @param estado 
 * @param entrada 
 * @param escribe 
 * @param movimiento 
 * @param sig_estado 
 */
void tupla_t::build(int estado, char entrada, char escribe, char movimiento, int sig_estado){
    estado_ = estado;
    entrada_ = entrada;
    escribe_ = escribe;
    movimiento_ = movimiento;
    sig_estado_ = sig_estado;
}

/**
 * @brief Destroy the tupla t::tupla t object
 * 
 */
tupla_t::~tupla_t(){}

/**
 * @brief Devuelve el valor del identificador, del estado
 * 
 * @return int 
 */
int tupla_t::get_identificador(){
    return estado_;
}

/**
 * @brief Devuelve el valor de la entrada
 * 
 * @return char 
 */
char tupla_t::get_entrada(){
    return entrada_;
}

/**
 * @brief Devuelve el valor de lo que se escribe en la cinta
 * 
 * @return char 
 */
char tupla_t::get_escribe(){
    return escribe_;
}

/**
 * @brief Devuelve el valor del movimiento
 * 
 * @return char 
 */
char tupla_t::get_movimiento(){
    return movimiento_;
}

/**
 * @brief Devuelve el valor del siguiente estado
 * 
 * @return int 
 */
int tupla_t::get_sig_estado(){
    return sig_estado_;
}
