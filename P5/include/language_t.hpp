#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

class language_t{
  private:
    set<string> L1;
	set<string> L2;


  public:
    language_t();
    ~language_t();

    void inversa();
    void concatenacion();
    void f_union();
    void interseccion();
    void diferencia();
    void sublenguaje();
    void igualdad_lenguajes();
    void potencia(int potencia);
    void cierre_kleene();

  private:
    set<string> concatenacion_2(set<string> L1, set<string> L2);

};
