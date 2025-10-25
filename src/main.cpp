#include "Mazo.h"
#include <iostream>
using namespace std;

int main() {
    Mazo* mazo = new Mazo(); // crea el mazo dinámicamente
    mazo->mostrarCartas();   // muestra todas las cartas
    delete mazo;             // libera memoria
    return 0;
}
