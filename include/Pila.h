#pragma once
#include <vector>
#include "Carta.h"

class Pila {
private:
    std::vector<Carta*> cartas;

public:
    void agregarCarta(Carta* carta);
    std::vector<Carta*> obtenerCartas() const;
    Carta* ultimaCarta();
    int tamano() const;
    void mostrar() const;
};
