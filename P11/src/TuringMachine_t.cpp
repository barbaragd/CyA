#include "../include/TuringMachine_t.hpp"

using namespace std;

/**
 * @brief Construct a new TuringMachine_t::TuringMachine_t object. 
 * Leer el fichero tanto de la máquina de turing como el de la cinta.
 * Detectar si hay algún error.
 * 
 * @param nombrefichero1 
 * @param nombrefichero2 
 * @param error 
 */
TuringMachine_t::TuringMachine_t(char nombrefichero1 [],char nombrefichero2 [], bool& error){
    string aux;

    // Leemos la cadena del fichero y la introducimos en un string "cinta".
    ifstream f_cinta(nombrefichero2);
    getline(f_cinta, cinta);

    ifstream turing(nombrefichero1);
    // Leemos el número de estados
    turing >> num_estados;
    getline(turing, aux); // Comprobamos que solo haya un valor en la línea.
    if(!aux.empty()){
        error = true;
        cout << "Error en la primera línea" << endl;
        return;
    }

    // Leer el estado de arranque
    turing >> e_arranque;
    getline(turing, aux); // Comprobamos que solo haya un valor en la línea.
    if(!aux.empty()){
        error = true;
        cout << "Error. Hay más de un estado de arranque." << endl;
        return;
    } 

    // Leer estado de aceptación
    turing >> estado_aceptacion;
    getline(turing, aux); // Comprobamos que solo haya un valor en la línea.
    if(!aux.empty()){
        error = true;
        cout << "Error en la tercera línea." << endl;
        return;
    } 

    // Leer cantidad de tuplas
    turing >> num_t_uplas;
    getline(turing, aux); // Comprobamos que solo haya un valor en la línea.
    if(!aux.empty()){
        error = true;
        cout << "Error en la cuarta línea." << endl;
        return;
    }  
    t_uplas.resize(num_t_uplas);    // Indicamos el tamaño del vector de tuplas con el num que
                                    // acabamos de leer (num_t_uplas)


    // Leer todas las tuplas.
    for(int i = 0; i<num_t_uplas; i++){
        // identificador
        int ident;
        turing >> ident; 

        // entrada , simbolo q se lee de la cinta
        char entrada;
        turing >> entrada;
        
        // escribe, simbolo que se escribe en la cinta
        char escribe;
        turing >> escribe;
        
        // movimiento = derecha, izquierda, parar
        char movimiento;
        turing >> movimiento;
        
        // sig estado
        int sig_estad;
        turing >> sig_estad;
        

        getline(turing, aux);
        if(!aux.empty()){
            error = true;
            cout << "Error en la definición de las tuplas." << endl;
            return;
        }  

        t_uplas.resize(num_t_uplas);
        t_uplas[i].build(ident, entrada, escribe, movimiento, sig_estad);

    }
    getline(turing, aux);
    if(!aux.empty()){
        error = true;
        cout << "Error en la definición de las tuplas." << endl;
        return;
    } 
}
/**
 * @brief Destroy the TuringMachine_t::TuringMachine_t object.
 * Limpiamos el vector de tuplas.
 * 
 */
TuringMachine_t::~TuringMachine_t(){
    t_uplas.clear();
}

/**
 * @brief Mostrar la maquina de turing. 
 * Mostramos los valores enteros, y luego recorremos el vector de tuplas.
 * 
 */
void TuringMachine_t::show_turing_machine(){
    cout << num_estados << endl; 
    cout << e_arranque << endl;
    cout << estado_aceptacion << endl;
    cout << num_t_uplas << endl;
    for(int j=0; j<num_t_uplas; j++){
        cout << t_uplas[j].get_identificador() << " " << t_uplas[j].get_entrada() << " " << t_uplas[j].get_escribe() << " " << t_uplas[j].get_movimiento() << " " << t_uplas[j].get_sig_estado() << endl;
    } 
    cout << endl;
}


/**
 * @brief Creo una cinta nueva de tipo string con un símbolo vacío al principio y al final.
 * 
 * Busco el estado de arranque entre las declaraciones de las tuplas.
 * Si no he encontrado el estado de arranque entre las tuplas, devuelvo false.
 * Si lo he encontrado, busco la transicion del estado actual que contenga el símbolo de la cinta 
 * que estoy señalando con j. Al principio este valor es 1 y no 0 porque en 0 está el símbolo vacío.
 * La función que me busca la transicion, si me devuelve el numero de tuplas significa que el símbolo 
 * de la cinta no está definido en las transiciones del estado actual. 
 * 
 * A continuación, si no me ha devuelto el número de tuplas, escribo en la cinta el símbolo a escribir 
 * definido en la transición del estado actual (e_act) y luego compruebo que movimiento realizo. 
 * Si es R, le sumo 1 a j, y si es L, le resto. Sin embargo, si es S, compruebo que el estado siguiente 
 * sea el de aceptación, y devuelvo true. Si no es así, devuelvo false. 
 * 
 * Luego, comparo el estado siguiente de mi estado actual, con todas las tuplas, y obtengo el siguiente
 * estado (la i, que es la posicion en el vector de tuplas) y establezco el estado actual (e_act).
 * 
 * Por último, muestro el recorrido.
 * 
 * @return true 
 * @return false 
 */
bool TuringMachine_t::simular_mt(){
    bool id = false;
    string vacio = "$";
    string temp = vacio + vacio + cinta + vacio + vacio;

    int i = 0;
    for(int it = 0; it < num_t_uplas; it++){
        if(e_arranque == t_uplas[it].get_identificador()){
            id = true;
            show_recorrido(temp, it+2, e_arranque); // +2 para colocarlo en el inicio de la cinta (sin contar los símbolos vacíos)
            it = num_t_uplas; // no recorrer más el for una vez encontrado una tupla con el símbolo de arranque
            i++;
        }
    }

    int e_act = e_arranque;
    unsigned j = 2; // 1 porque el primer y segundo valor es el símbolo vacío
    if(id == false){
        return false;
    }
    else{
        while(i < num_t_uplas){
            i = lookfor_transicion(temp[j], e_act);
            if(i == num_t_uplas){
                return false;
            }
            else{
                temp[j] = t_uplas[i].get_escribe();
                if(t_uplas[i].get_movimiento() == 'R'){
                    j++;
                }
                else if(t_uplas[i].get_movimiento() == 'L'){
                    j--;
                }
                else{
                    if(t_uplas[i].get_sig_estado() == estado_aceptacion){
                        show_recorrido(temp, j, t_uplas[i].get_sig_estado());
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                for(int k=0; k<num_t_uplas; k++){
                    if(t_uplas[k].get_identificador() == t_uplas[i].get_sig_estado()){
                        e_act = t_uplas[i].get_sig_estado();
                        i = k;
                        k = num_t_uplas; // parar de recorrer el for
                    }
                }
                show_recorrido(temp, j, e_act);
            }
        } 

    }
    return false;
}


/**
 * @brief Paso la cinta temporal, la posición a la que estoy apuntando en la cinta, y el estado actual.
 * 
 * Primero muestro la cinta hasta que llego a la posición señalada por j, a continuación muestro
 * el estado actual, y por último el resto de la cinta. 
 * 
 * @param temp 
 * @param j 
 * @param e_act 
 */
void TuringMachine_t::show_recorrido(string& temp, unsigned j, int e_act){
    for(unsigned i=0; i<j; i++){
        cout << temp[i];
    }
    cout << " q" << e_act << " ";
    for(unsigned i=j; i<temp.size(); i++){
        cout <<  temp[i];
    }
    cout << endl;
}

/**
 * @brief Paso como parámetros el símbolo de la entrada y el estado_actual definido en id.
 * 
 * Recorro todas las tuplas, y cuando el identificador sea igual el id, compruebo si la
 * entrada de esta tupla coincide con la entrada que estoy buscando. Si es así, devuelvo
 * la posición de la tupla en el vector de tuplas. Si no es así sigo recorriendo las entradas
 * de la tupla con el identificador igual a id.
 * 
 * Si al terminar de recorrer las tuplas no encuentro la entrada que estoy buscando,
 * devuelvo el numero de tuplas, que sería una posición que no existe en mi vector.
 * 
 * @param ent 
 * @param id 
 * @return int 
 */
int TuringMachine_t::lookfor_transicion(char ent, int id){
    for(int i=0; i<num_t_uplas; i++){
        if(t_uplas[i].get_identificador() == id){
            if(t_uplas[i].get_entrada() == ent){
                return i;
            }
        }
    }
    return num_t_uplas; // si no encuentro la transicion devuelvo el número de tuplas,
                        // dicho valor no será ninguna posición del vector de tuplas
}

