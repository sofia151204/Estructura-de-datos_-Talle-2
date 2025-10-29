/* CartaComodin.h
#ifndef CARTA_COMODIN_H
#define CARTA_COMODIN_H
#include "Carta.h"

class CartaComodin : public Carta {
    bool esDorado;
public:
    CartaComodin(bool esDorado = false)
        : Carta(esDorado ? "Comodín Dorado" : "Comodín"), esDorado(esDorado) {}
    void mostrar() const override {
        std::cout << "Carta " << (esDorado ? "Comodín Dorado" : "Comodín") << std::endl;
    }
};

#endif
*/