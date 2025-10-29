/* CartaUltimaRonda.h
#ifndef CARTA_ULTIMA_RONDA_H
#define CARTA_ULTIMA_RONDA_H
#include "Carta.h"

class CartaUltimaRonda : public Carta {
public:
    CartaUltimaRonda() : Carta("Última Ronda") {}
    void mostrar() const override {
        std::cout << "Carta de Última Ronda" << std::endl;
    }
};

#endif
*/