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

    /*set<char>::iterator it = v_.begin();
    for(unsigned i=0; i<dfa.get_c_estados(); i++){
        P_[i].first = *it;
        it++;
        //P_[i].second.push_back
    }*/
    
    // reglas de producción
    //P_.resize(dfa.get_c_estados());

    // unsigned ids;
    // char t;
    // char nt;
    // for(int i=0; i<dfa.get_c_estados(); i++){
    //     estado_t aux = dfa.get_estado(i);
    //     for(set<char>::iterator al=alfabeto_.begin(); al!=alfabeto_.end(); al++){
    //         t = *al;
    //         ids = aux.get_next(t);
    //         for(int j=0; j<simbolos.size(); j++){
    //             if(ids == simbolos[j].first){
    //                 nt = simbolos[j].second;
    //             }
    //         }
    //         P_[i].push_back(t); 
    //         P_[i].push_back(nt); 
    //         P_[i].push_back('|'); 
    //     }
    //     if(aux.if_aceptacion()==true){
    //         P_[i].push_back('~');
    //     }
    // }

}


/**
 * @brief Construct a new gr t::gr t object
 * 
 * @param nombre 
 */
GR_t::GR_t(char nombre[]){
    string auxleer;
    ifstream gra(nombre);
    
    // Símolos terminales
    int n_sim_ter;
    int contar=0;
    gra >> n_sim_ter; // Línea 1: número total de símbolos terminales que posee la gramática
    getline(gra, auxleer);
    if(!auxleer.empty()){
        cout << "Error en la primera línea" << endl;
        return;
    }
    auxleer.erase();
    

    getline(gra, auxleer); // Línea 2: lista de todos los símbolos terminales de la gramática.
    string::iterator it;
    for(it=auxleer.begin(); it!=auxleer.end(); it++){
        if(*it != ' '){
            alfabeto_.insert(*it);
        }
    }
    if(alfabeto_.size() != n_sim_ter){
        cout << alfabeto_.size() << "," << n_sim_ter << endl;
        cout << "No coinciden el número total de símbolos terminales (Línea 1) con la lista de dichos símbolos(Línea 2)" << endl;
        return;
    }

    auxleer.erase();

    // Símolos no terminales
    int n_sim_nter;
    contar=0;
    gra >> n_sim_nter;  // Línea 3: número total de símbolos no terminales que posee la gramática
    getline(gra, auxleer);
    if(!auxleer.empty()){
        cout << "Error en la tercera línea" << endl;
        return;
    }
    auxleer.erase();


    getline(gra, auxleer); // Línea 4: lista de todos los símbolos no terminales de la gramática.
    //string::iterator it;
    for(it=auxleer.begin(); it!=auxleer.end(); it++){
        if(*it != ' '){
            v_.insert(*it);
        }
    }
    if(v_.size() != n_sim_nter){
        cout << v_.size() << "," << n_sim_nter << endl;
        cout << "No coinciden el número total de símbolos no terminales (Línea 3) con la lista de dichos símbolos(Línea 4)" << endl;
        return;
    }
    /*set<char>::iterator x;
    x = v_.find('S');
    v_.erase(x);*/

    // Producciones
    P_.resize(v_.size());

    char flecha1 = '-';
    char flecha2 = '>';
    string leer;
    vector <char> m;
    int j=0;
    // Primera producción, la inicial               // string::iterator it;
    P_[0].first = 'S';
    getline(gra, leer);
    leer.push_back('|');

    it=leer.begin();
    string::iterator aux;
    aux = leer.begin();
    it++; // el primer carácter es el símbolo no terminal
    while(it!=leer.end()){
        //cout << *it << " ";
        if((*it =='-')|| (*it == '>') || (*it == ' ')){
            it++;
        }
        else{
            if((*it == '|')){
                P_[0].second.push_back(m);
                m.clear();
            }
            else {
                //cout << *it << " // ";
                m.push_back(*it);
            }
            it++;
        } 
    } 


    // Las demás producciones
    j=0;
    for(int i=1; i<v_.size(); i++){
        getline(gra, leer);
        leer.push_back('|');
        it=leer.begin();
        P_[i].first = *it; 
        it++;
        while(it!=leer.end()){
            if((*it == '-') || (*it == '>') || (*it == ' ')){
                it++;
            }
            else{
                if(*it == '|'){
                    P_[i].second.push_back(m);
                    m.clear();
                }
                else {
                    m.push_back(*it);
                }
                it++;
            }
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
    cout << alfabeto_.size() << endl;

    // lista de todos los símbolos terminales de la gramática
    for(set<char>::iterator al=alfabeto_.begin(); al!=alfabeto_.end(); al++){
        sal << (*al) << " ";
        cout << (*al) << " ";
    }
    sal << endl;
    cout << endl;


    // número total de símbolos no terminales que posee la gramática
    sal << v_.size() << endl;
    cout << v_.size() << endl;

    // lista de todos los símbolos no terminales de la gramática
    for(set<char>::iterator i=v_.begin(); i!=v_.end(); i++){
        sal << (*i) << " ";
        cout << (*i) << " ";
    }
    sal << endl;
    cout << endl;

    // reglas de producción del inicial
    int k = 0;
    set<char>::iterator it = v_.find('S');
    sal << (*it) << "->";   
    cout << (*it) << "->";  
    vector<char> prod;
    for(int i=0; i<P_[0].second.size(); i++){
        prod = P_[0].second.at(i);
        for(int j=0; j<prod.size(); j++){
            sal << prod[j];
            cout << prod[j];
        }
        sal << '|';
        cout << '|';
    }
    sal << endl;
    cout << endl;
    set<char>::iterator j = v_.find('S');
    v_.erase(j);


    // reglas de producción 
    //set<char>::iterator it;
    k = 1;
    ;
    for(set<char>::iterator it=v_.begin(); it!=v_.end(); it++){
        sal << (*it) << "->";
        cout << (*it) << "->"; 
        for(int i=0; i<P_[k].second.size(); i++){
            prod = P_[k].second.at(i);
            for(int j=0; j<prod.size(); j++){
                sal << prod[j];
                cout << prod[j];
            }
            sal << '|';
            cout << '|';
        }
        k++;
        sal << endl;
        cout << endl;
    }
    sal.close();
}


/**
 * @brief Método para no introducir producciones repetidas, para ello paso i, que indica en que no terminal 
 * (de la derecha) quiero comprobar que no hayan produccions vacías, y paso la produccion que quiero
 * comprobar que no se repita.
 * 
 * Creo una variable contador que contará los char del vector que se repetirán. Recorro las producciones,
 * y si son del mismo tamaño que la produccion que le he pasado como parámetro, compruebo a ver si los 
 * símbolos (terminal o no) de cada produccion son iguales a ella. Por cada una que sea igual, incremento
 * el contador. Si al final el contador coincide con el tamaño de p pues entonces la producción es repetida
 * y no tengo que añadirla.
 * Devuelve true si la produccion no es repetida, y false si sí lo es.
 * 
 * @param i 
 * @param p 
 * @return true 
 * @return false 
 */
bool GR_t::prod_repetida(int i, vector<char> p){
    int c = 0;
    for(int j=0; j<P_[i].second.size(); j++){
        if(P_[i].second[j].size() == p.size()){
            for (int k=0; k<P_[i].second[j].size(); k++){
                if(p[k] == P_[i].second[j][k]){
                    c++;
                }
            }
            if(c==p.size()){
                return false;
            }
            c=0;
        }
    }
    return true;
}


/**
 * @brief Algoritmo para eliminar las producciones vacías.
 * Algoritmo para eliminar las produccions vacías. Primero introduzco en H los símbolos no terminales que me dan la cadena vacía. Luego introduzco los símbolos no terminales
 * que llegan a esos símbolos no terminale introducidos previamente en H. A continuación, hago todas las producciones quitando los símbolos no terminales que hay en H. Por 
 * último, si la cadena vacía pertenece al lenguaje, o si S está en H, la cadena vacía se debe de introducir en S. 
 * 
 */
void GR_t::eliminar_prod_vacias(){
    
    int flag=0;
    set<char> H;
    set<char> H_vieja;
    for(int i=0; i<v_.size(); i++){ // inicialización 
        for(int j=0; j<P_[i].second.size(); j++){
            if(P_[i].second[j][0] == '~'){
                H.insert(P_[i].first);
                P_[i].second[j].pop_back();
                P_[i].second.resize(P_[i].second.size()-1);
                flag = 1;
            }
        }
    }

    int h=0;
    char aux;
    while(H_vieja != H){
        H_vieja = H;
        for(int i=0; i<v_.size(); i++){
            for(int j=0; j<P_[i].second.size(); j++){
                h = 0;
                for (int k=0; k<P_[i].second[j].size(); k++){
                    for(set<char>::iterator it=H.begin(); it!=H.end(); it++){
                        if(P_[i].second[j][k] == *it){
                            h++;
                        }
                    }
                    if(h == H.size()){
                        aux = P_[i].first;
                    }
                }
                if ((h == P_[i].second[j].size()) && (h != 0)){
                    H.insert(aux);
                }
            }
        }
    }

    int w=0;
    int max;
    int f=0;
    for(int i=0; i<v_.size(); i++){
        for(int j=0; j<P_[i].second.size(); j++){
            for (int k=0; k<P_[i].second[j].size(); k++){ 
                for(set<char>::iterator it=H.begin(); it!=H.end(); it++){
                    if(P_[i].second[j][k] == *it){
                        max = P_[i].second[j].size();
                        vector<char> aux;
                        w=0;
                        while(w<max){
                            if (k == w){
                                w++;
                            }
                            else{
                                f = 1;
                                aux.push_back(P_[i].second[j][w]);
                                w++;
                            }
                            //w++;
                        } 
                        if (f==1){
                            if(prod_repetida(i, aux) == true){
                                P_[i].second.push_back(aux);
                            }
                            f=0;
                        }
                    }
                }
            }
        }
    }


    // Si S está en el conjunto H hay que añadirle la producción '~'
    int x=0;
    vector<char> cad_vacia;
    cad_vacia.push_back('~');
    for(set<char>::iterator it=H.begin(); it!=H.end(); it++){
        if('S' == *it){
            x = 1;
            P_[0].second.push_back(cad_vacia);
        }
    }

    // Si S no está en H pero la cadena vacía pertenece al lenguaje, hay que añadirle dicha cadena
    if(flag == 1 && x == 0){
        P_[0].second.push_back(cad_vacia);
    }
    

}


/**
 * @brief Envío como parámetros el conjunto H que contiene parejas de no terminales, de la forma A->B, 
 * un char a que indica el primer miembro de la pareja, de manera que con este método obtengo el 
 * segundo miembro de la pareja. Envío por referencia un flag para que si pareja existe, se active, 
 * y si no existe, pues que no se active y tenerlo en cuenta. 
 * 
 * @param H 
 * @param a 
 * @param flag 
 * @return char 
 */
char GR_t::get_next(set<pair<char,char>>& H, char a, int& flag){
    pair<char,char> aux;
    for(set<pair<char,char>>::iterator it=H.begin(); it!=H.end(); it++){
        aux = *it;
        if(aux.first == a){
            flag = 1;
            return aux.second;
        }
    }
    flag = 0;
}

/**
 * @brief Insertar producciones.
 * 
 * Se pasan como parámetros el símbolo no terminal (x), cuyas producciones quiero insertar
 * en el no terminal indicado por el parámetro no_ter, y las producciones del no terminal indicado
 * por el parámetro no_ter
 * 
 * Recorro los no terminales, y cuando consigo el que es igual a x, añado todas sus producciones al
 * terminal indicado por no_ter, teniendo en cuenta no añadir ninguna repetida.
 * 
 * @param x 
 * @param pr 
 * @param no_ter 
 */
void GR_t::insertar_prod(char x, pair<char, vector<vector<char>>>& pr, int no_ter){
    vector<char> produccion;
    for(int i=0; i<v_.size(); i++){
        if(P_[i].first == x){
            for(int j=0; j<P_[i].second.size(); j++){
                produccion = P_[i].second[j];
                if(prod_repetida(no_ter, produccion) == true){ 
                    pr.second.push_back(produccion);
                }
            }
        }
    }
}


/**
 * @brief Borrar producciones.
 * 
 * Paso como parámetros las producciones, y la posición de la producción que quiero borrar.
 * 
 * Creo un vector donde guardaré el vector con todas las producciones que quiero.
 * 
 * Recorro las producciones de P, cuando llego a la producción del mismo índice que la posición
 * que quiero borrar, pues esa producción no la inserto en el vector creado.
 * 
 * Si nunca inserto nada en el vector nuevo, significa que solo hay una producción, y por lo tanto
 * hago un push_back; si retornara el vector creado vacío me daría violación de segmento. 
 * 
 * @param e 
 * @param P 
 * @return vector<vector<char>> 
 */
vector<vector<char>> GR_t::borrar_prod(int e, vector<vector<char>> P){
    vector<vector<char>> P_aux;
    for(int i=0; i<P.size(); i++){
        if(i != e){
            P_aux.push_back(P[i]);
        }
    }
    if(P_aux.empty()){
        P[e].pop_back();
        return P;
    }
    else return P_aux;
}


/**
 * @brief Eliminar producciones unitarias, de la forma A->B.
 * 
 * Inserto en mi conjunto de parejas de la forma A->B, todas las producciones unitarias que existan,
 * y las elimino. 
 * 
 * A continuación compruebo las parejas creadas, de manera que busco conseguir más producciones 
 * unitarias que pueda eliminar. 
 * 
 * Por último, teniendo en cuenta las parejas del conjunto H, añado las producciones nuevas. 
 * 
 */
void GR_t::eliminar_prod_unitarias(){

    set<pair<char,char>> H;
    pair<char,char> aux;
    for(int i=0; i<v_.size(); i++){
        for(int j=0; j<P_[i].second.size(); j++){
            if(P_[i].second[j].size() == 1){
                for(set<char>::iterator it=v_.begin(); it!=v_.end(); it++){
                    if(P_[i].second[j][0] == *it){
                        aux.first = P_[i].first;
                        aux.second = *it;
                        H.insert(aux); 
                        P_[i].second = borrar_prod(j, P_[i].second); // eliminar prod unitarias
                    }
                }
            }
        }
    }

    pair<char,char> x;
    char t;
    int flag = 0;
    for(set<pair<char,char>>::iterator it=H.begin(); it!=H.end(); it++){
        x = *it;
        t = get_next(H , x.second, flag);
        if(flag == 1){
            
            aux.first = x.first;
            aux.second = t;

            H.insert(aux);
            flag = 0;

        }
    }

    for(set<pair<char,char>>::iterator it=H.begin(); it!=H.end(); it++){
        x = *it;
        for(int i=0; i<v_.size(); i++){
            if(x.first == P_[i].first){
                insertar_prod(x.second, P_[i], i);
            }
        }
    }

}
