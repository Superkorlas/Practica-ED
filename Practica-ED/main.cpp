#include "conjunto.h"
#include "CSS.h"
#include "crimen.h"
#include "fecha.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <functional>

using namespace std;

int main() {

    CSS prueba;
    
    //Prueba de load:
    prueba.load("crimenes.csv");
    
    //Prueba de cout:
    cout << prueba;
    
    //Prueba de setArrest:
    const ID id = 10233462;
    prueba.setArrest(id, true);
    
    //Prueba de método inArea:
    list<ID> lista = prueba.inArea(-100,-100,100,100);
    for (auto i = lista.begin(); i != lista.end(); i++)
        cout << *i << "\n";
    
    return 0;
}
