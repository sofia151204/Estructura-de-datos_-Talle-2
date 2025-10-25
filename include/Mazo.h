#ifndef MAZO_H
#define MAZO_H

#include <string>
#include "CartaColor.h"
#include "CartaMasDos.h"
#include "CartaComodin.h"
#include "CartaUltimaRonda.h"

class Mazo {
    Carta** cartas;
    int cantidad;
public:
    Mazo();
    void mostrarCartas() const;
    ~Mazo();
};

#endif
