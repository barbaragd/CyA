#include "dfa_t.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <iterator>

using namespace std;

/**Establecer estado de arranque**/
void DFA_t::set_earranque(unsigned x){
    e_arranque_ = x;
}

unsigned DFA_t::get_earranque(){
    return e_arranque_;
}

/**Constructor**/
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

DFA_t::DFA_t(){}

/**Destructor**/
DFA_t::~DFA_t(){}

/**Mostrar DFA**/
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


/**Indicar cuantos estados de muerte y cuáles son**/
void DFA_t::estados_muerte(){
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
                cout << aux.get_identificador() << ",";
            }
        }
    cout << endl;
    }
    else {
        cout << "No hay estados de muerte." << endl;
    }
}
/**Leer la cadena de entrada**/
void DFA_t::leer_cadena(string cadena){
    set<estado_t>::iterator it;
    estado_t aux;
    unsigned id = e_arranque_;

    vector<unsigned> est;

    leer_rec(cadena, est, id, 0);


}

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


/**MINIMIZAR**/
void DFA_t::minimize(DFA_t& dfa_min){

	set<set<estado_t>> PI;
	set<set<estado_t>> PI_vieja;

	//Particion inicial
	set<estado_t> a;
	set<estado_t> n_a;

    int contador=1; // contar los conjuntos

    set<estado_t>::iterator it;
    estado_t aux;
	for(it=estados_.begin(); it!=estados_.end(); it++){
        aux = *it;
		if(aux.if_aceptacion()==true)
			a.insert(aux);
		else
			n_a.insert(aux);
	}
	PI.insert(a);
	PI.insert(n_a);

    set<estado_t> c_aux;
    estado_t e_aux;
    cout<<"P0: {";
    for (set<set<estado_t>>::iterator i= PI.begin(); i != PI.end(); i++){
        set<estado_t> c_aux = *i;
        cout<<"{";
        for (set<estado_t>::iterator j = c_aux.begin(); j != c_aux.end(); j++){
            e_aux = *j;
            cout<< e_aux.get_identificador()<<",";
        }
        cout<<"} ";
    }
    cout<<"}"<<endl;	
    
    // Nuevas particiones
	while(PI != PI_vieja){
		PI_vieja = PI;
		PI = new_part(PI_vieja, contador);
	}
    unsigned e = e_arranque_;
    int cont=PI.size();
    cout << "El DFA mínimo tiene " << cont << " estados" << endl;

    // Construir el DFA
    build_DFA(PI, e, cont);
    // Exportar DFA
    exportar_dfa();
}

// Crear nueva partición
set<set<estado_t>> DFA_t::new_part(set<set<estado_t>>  PI_vieja, int& contador){
    set<set<estado_t>> PI;
    set<set<estado_t>> G;
    set<estado_t> aux; // conjuntos de PI
    set<set<estado_t>>::iterator it;

    for(it=PI_vieja.begin(); it!=PI_vieja.end(); it++){
        aux = *it;
        G = descomponer(aux, PI_vieja, contador);
        PI.insert(G.begin(), G.end());
    }
    return PI;
}

set<set<estado_t>> DFA_t::descomponer(set<estado_t> conjunto, set<set<estado_t>>  PI_vieja, int& contador){
    char s;
    set<char>::iterator i;
    set<set<estado_t>>::iterator j;

    set<set<estado_t>> T;
    set<set<estado_t>> aux;
    T.insert(conjunto);

    for(i=alfabeto_.begin(); i!=alfabeto_.end(); i++){
        set<set<estado_t>> P_;
        s = *i;
        for(j=T.begin(); j!=T.end(); j++){
            aux = part((*j), s, PI_vieja);
            P_.insert(aux.begin(), aux.end());
        }
        T = P_;


        writePart(T, contador, s, conjunto, PI_vieja);
    }

    return T;
}



set<set<estado_t>> DFA_t::part(set<estado_t> G, char simbolo, set<set<estado_t>> PI_vieja){
    
    set<set<estado_t>> R_;
    set<estado_t> H;

    set<set<estado_t>>::iterator ita;
    set<estado_t>::iterator itb;
    set<estado_t>::iterator itc;

    estado_t auxa;
    estado_t auxb;

    for(ita=PI_vieja.begin(); ita!=PI_vieja.end(); ita++){
        H = *ita;
        set<estado_t> c;
        for(itb=G.begin(); itb!=G.end(); itb++){
            auxa = *itb;
            for(itc=H.begin(); itc!=H.end(); itc++){
                auxb = *itc;
                if(auxa.get_next(simbolo) == auxb.get_identificador()){
                    c.insert(auxa);
                }

            }
        }
        if(c.empty()==false){
            R_.insert(c);
        }
    }
    return R_;
}

/**Mostrar las particiones**/
void DFA_t::writePart(set<set<estado_t>>particion, int& contador, char s, set<estado_t> G, set<set<estado_t>> PI){
	set<estado_t> c_aux;
    estado_t e_aux;
    set<set<estado_t>>::iterator ita;
    set<estado_t>::iterator itb;

	cout << "Con el símbolo " << s << " :" << endl;
    cout << "P" << contador << ":{";
	for(ita = particion.begin(); ita!=particion.end(); ita++){
        c_aux = *ita;
        cout<<"{";
		for(itb = c_aux.begin(); itb!=c_aux.end(); itb++){
			e_aux = *itb;
            cout << e_aux.get_identificador() << ",";
		}
		cout << " } ";
	}

    for (ita = PI.begin(); ita != PI.end(); ita++){
        c_aux = *ita;
        if(c_aux != G){
            cout << "{";
            for(itb=c_aux.begin(); itb!=c_aux.end(); itb++){
                e_aux = *itb;
                cout << e_aux.get_identificador() << ",";
            }
            cout<<"} ";
        }
    }

	cout << " }" <<endl;
    contador++;
}
/**END MINIMIZAR**/


/**Mostrar la lectura de la cadena**/
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

/**Construcción del DFA minimizado**/
void DFA_t::build_DFA(set<set<estado_t>> PI, unsigned e_arranque, int cont){  
    estados_.clear();
    set_earranque(e_arranque);
    unsigned b = get_earranque();

    pair<char,unsigned> m;
    estado_t aux;
    
    set<estado_t> conjunto;
    set<set<estado_t>>::iterator i;
    set<estado_t>::iterator j;

    for(i=PI.begin(); i!=PI.end(); i++){
        conjunto = *i;

        // for(j=conjunto.begin(); j!=conjunto.end(); j++){
            j=conjunto.begin();
            estado_t estado;
            aux = (*j);
            if(aux.if_aceptacion()==true){
                estado.set_aceptacion(true);
            }
            else{
                estado.set_aceptacion(false);
            }
            estado.set_identificador(b);
            for(int k=0; k<aux.get_c_transicion(); k++){
                m = aux.get_transiciones(k);
                estado.set_transiciones(m);
            }
            estado.set_c_transicion(aux.get_c_transicion());
            b++;
            estados_.insert(estado);
        //}
    }
}


/**Exportar el fichero minimizado**/
void DFA_t::exportar_dfa(){
    char nombrefichero[20];
    cout << "Introduzca el nombre del fichero: [.dfa]: ";
    cin >> nombrefichero;
    ofstream sal(nombrefichero);


    sal << estados_.size() << endl;
    sal << get_earranque() << endl;

    set<estado_t>::iterator it;
    for(it=estados_.begin(); it!=estados_.end(); it++){
        estado_t aux;
        aux = *it;
        sal << aux.get_identificador() << " " << aux.if_aceptacion() << " " << aux.get_c_transicion();
        for(int j=0; j<aux.get_c_transicion(); j++){
            sal << " " << aux.get_first(j) << " " << aux.get_next(aux.get_first(j));
        }
        sal << endl;
    }
    sal.close();
}
