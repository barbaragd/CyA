#pragma once
using namespace std;


/**
 * @brief Clase tupla_t. Contiene el estado, la entrada, el simbolo a escribir en la cinta,
 * el movimiento indicado con un char (R, derecha; L, izquierda; S, parar) y el sig
 * estado al que se transita.
 * 
 */
class tupla_t{
    private:
        int estado_;
        char entrada_;
        char escribe_;
        char movimiento_;
        int sig_estado_;


    public:
        tupla_t();
        tupla_t(int estado, char entrada, char escribe, char movimiento, int sig_estado);
        void build(int estado, char entrada, char escribe, char movimiento, int sig_estado);
        ~tupla_t();

        int get_identificador();
        char get_entrada();
        char get_escribe();
        char get_movimiento();
        int get_sig_estado();

};