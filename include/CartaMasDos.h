// CartaMasDos.h
#ifndef CARTA_MASDOS_H
#define CARTA_MASDOS_H
#include "Carta.h"

class CartaMasDos : public Carta {
public:
    CartaMasDos() : Carta("+2") {}
    void mostrar() const override {
        std::cout << "Carta +2" << std::endl;
    }
};

#endif
