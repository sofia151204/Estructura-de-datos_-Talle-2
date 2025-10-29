#include "Pila.h"
#include <iostream>

void Pila::agregarCarta(Carta* carta) {
    cartas.push_back(carta);
}

std::vector<Carta*> Pila::obtenerCartas() const {
    return cartas;
}

Carta* Pila::ultimaCarta() {
    if (cartas.empty()) return nullptr;
    return cartas.back();
}

int Pila::tamano() const {
    return cartas.size();
}

void Pila::mostrar() const {
    if (cartas.empty()) {
        std::cout << "[vacía]";
    } else {
        for (auto c : cartas) std::cout << c->getColor() << " ";
    }
    std::cout << "\n";
}
