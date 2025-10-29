#pragma once
#include <vector>
#include "Carta.h"
#include <iostream>


class Pila {
private:
    std::vector<Carta*> cartas;
public:
    Pila() = default;
    ~Pila() = default;

    void agregarCarta(Carta* carta);
    std::vector<Carta*> obtenerCartas() const;
    void vaciar();
    int tamano() const;
    void mostrar() const;
    void ultimaCarta();
};
