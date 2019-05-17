#include "language_t.hpp"

using namespace std;

language_t::language_t(){

	int n_cad;
	string cad_1, cad_2;

	set<string>::iterator it;


	// LENGUAJE 1
	cout << "[Lenguaje 1]: " << endl;
	cout << "Número de cadenas del lenguaje: ";
	cin >> n_cad;
	
	for(int i=0; i<n_cad; i++){
		cout << "Cadena "<< i+1 << ": ";
		cin >> cad_1;
		L1.insert(cad_1);
	}
	
	cout << "El lenguaje 1: {";
	for(it= L1.begin(); it!= L1.end(); it++){
		cout << (*it) << ", ";
	}
	cout << "}";
	cout << endl << endl;
	
	
	// LENGUAJE 2
	cout << "[Lenguaje 2]: " << endl;
	cout << "Número de cadenas del lenguaje: ";
	cin >> n_cad;
	
	for(int i=0; i<n_cad; i++){
		cout << "Cadena "<< i+1 << ": ";
		cin >> cad_2;
		L2.insert(cad_2);
	}
	
	cout << "El lenguaje 2: {";
	for(it= L2.begin(); it!= L2.end(); it++){
		cout << (*it) << ", ";
	}
	cout << "}";
	cout << endl << endl;

}

language_t::~language_t(){}


// INVERSA
void language_t::inversa(){

	set<string>::iterator i;

	for(i=L1.begin(); i!=L1.end(); i++){
		string inver=*i;
		inver = string(inver.rbegin(), inver.rend());
		cout << inver << ",";
	}

}


// CONCATENACION
// 1 metodo
void language_t::concatenacion(){
	
	set<string>::iterator i;
	set<string>::iterator j;
	for(i=L1.begin(); i!=L1.end();i++){
		for(j=L2.begin(); j!=L2.end();j++){
			cout <<*i<<*j<<", ";
		}
	}
}

// 2 metodo, lo utilizo para la potencia
set<string> language_t::concatenacion_2(set<string> L1, set<string> L2){
	set<string>::iterator i;
	set<string>::iterator j;
	string cadena;
	set<string> L_res;
	for(i=L1.begin(); i!=L1.end();i++){
		for(j=L2.begin(); j!=L2.end();j++){
			cadena = (*i) + (*j);
			L_res.insert(cadena);
		}
	}
	return L_res;
}



// UNION
void language_t::f_union(){
/*	cout << "Union: ";
	ostream_iterator< string > iter( cout, " " );
	set_union(L1.begin(), L1.end(), L2.begin(), L2.end(), iter);
    cout << endl;*/

	set<string>::iterator i;
	set<string> L_res;
	L_res.insert(L1.begin(), L1.end());
	L_res.insert(L2.begin(), L2.end());

	for (i = L_res.begin(); i != L_res.end(); i++){
		cout <<(*i)<<", "; 
	}
}


// INTERSECCION
void language_t::interseccion(){
/*	ostream_iterator< string > iter( cout, " " );
    cout << "Interseccion: ";
	set_intersection(L1.begin(), L1.end(), L2.begin(), L2.end(), iter);    
	cout << endl;
*/
	set<string> L_res;
	set<string>::iterator i;
	set<string>::iterator j;
	for (i = L1.begin(); i != L1.end(); i++){
		for (j = L2.begin(); j != L2.end(); j++){
			if((*i)==(*j)){
			   L_res.insert(*i);
			}
		}
	}
	
	if(L_res.empty()) cout << "&" << endl;
	
	else{
		for(i=L_res.begin(); i!= L_res.end(); i++){
    		cout << (*i) << ", ";
  		}
  	}
}


// DIFERENCIA
void language_t::diferencia(){
/*	ostream_iterator< string > iter( cout, " " );
	
	set<string> L_res;  
	set_difference(L1.begin(), L1.end(), L2.begin(), L2.end(),inserter(L_res, L_res.begin()));

	cout << "Set C (difference of A and B): ";
	copy(L_res.begin(), L_res.end(), iter);
	cout << endl;*/
	
	
	set<string> L_res;
	set_difference(L1.begin(), L1.end(), L2.begin(), L2.end(), inserter(L_res, L_res.begin()));
	
	set<string>::iterator i;
	
	if(L_res.empty()) cout << " ";
	
	else {
		for(i=L_res.begin(); i!=L_res.end(); i++){
			cout << (*i) << ", ";
		}
	}
}


// SUBLENGUAJE
void language_t::sublenguaje(){
	
	set<string>::iterator i;
	set<string>::iterator j;
	int l=0;
	
	if(L2.size()>L1.size()){
		cout << "El lenguaje 2 no es sublenguaje del lenguaje 1." << endl;
	}
	
	else{
		for(i = L1.begin(); i != L1.end(); i++){
			for(j = L2.begin(); j != L2.end(); j++){
				if(*i==*j){
					l++;	
				}
			}	
		}
		if (l==L2.size()) cout << "El lenguaje 2 es sublenguaje del lenguaje 1" << endl;
		else cout << "El lenguaje 2 no es sublenguaje del lenguaje 1" << endl;
	}

}


// IGUALDAD DE LENGUAJES
void language_t::igualdad_lenguajes(){
	
	if(L1.size()!=L2.size()) cout << "Lenguajes diferentes" << endl;
	else{
		int igualdad = 0;
		set<string>::iterator i;
		set<string>::iterator j;
		i = L1.begin();
		j = L2.begin();
		while(i != L1.end()){
			if(*i == *j) igualdad++;
			i++; j++;
		}
		if(igualdad==L1.size()) cout << "Lenguajes iguales" << endl;
		else cout << "Lenguajes diferentes" << endl;
	}

}


// POTENCIA
void language_t::potencia(int potencia){
	int k=1;
	
	set<string> L_potencia = L1;
	set<string>::iterator i;
	
	if(potencia==0){
		cout << "&";
	}
	else if(potencia==1){
		for(i=L1.begin(); i != L1.end(); i++){
			cout << (*i) << ",";
		}
	}
	else {
		while(k<potencia){
			L_potencia = concatenacion_2(L_potencia, L1);	
			k++;	
		}
		for(i=L_potencia.begin(); i != L_potencia.end(); i++){
			cout << (*i) << ",";
		}
	}
}


// CIERRE DE KLEENE
void language_t::cierre_kleene(){
	potencia(0);
	cout << ",";
	for(int i=1; i<=2; i++){
		potencia(i);
	}	
}






