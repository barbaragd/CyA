bool DFA_t::leer_cadena(string cadena){
    //for(int i=0; i<cadena.length(); i++){
    unsigned id = e_arranque_;
    //cout << id << " ";
    int i=0;
    int no=0;
    estado_t aux;
    set<estado_t>::iterator it=estados_.begin();
    vector<unsigned> est;
    
    while(i<cadena.length()){
        aux = *it;
        no = 0;
        if(aux.get_identificador() == id){
            for(int j=0; j<aux.get_c_transicion(); j++){
                if(cadena.at(i) == aux.get_first(j)){
                    cout << "aqui1" << endl;
                    id = aux.get_second(j);
                    est.push_back(id);
                    j = aux.get_c_transicion();
                }
                else no++;
                cout << "aqui2" << endl;
            }
            cout << endl;
            if(no == aux.get_c_transicion())
                return false;
            i++;
        }
        it++;
        cout << "aqui3" << endl;
    }
    
    for(it=estados_.begin(); it!=estados_.end(); it++){
        aux = *it;
        if(aux.get_identificador() == id){
            if(aux.if_aceptacion()==true){
                write(cadena, est);
                return true;
            } 
            else{
                write(cadena, est);
                return false;
            }
        }
    }
}
