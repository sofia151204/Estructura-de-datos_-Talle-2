#pragma once
#include <vector>
#include "Carta.h"

class Pila {
private:
    std::vector<Carta*> cartas;
public:
    Pila() = default;
    // agrega una carta a la pila (la carta pasa a ser propiedad del juego/pila)
    void agregarCarta(Carta* c) { cartas.push_back(c); }

    // retorna las cartas (por copia de punteros) para transferirlas al jugador
    std::vector<Carta*> obtenerCartas() const { return cartas; }

    // vacía la pila (sin borrar las cartas; se asume que el receptor tomará la propiedad)
    void vaciar() { cartas.clear(); }

    // muestra la pila
    void mostrar() const {
        if (cartas.empty()) {
            std::cout << "[vacía]";
            return;
        }
        for (auto c : cartas) {
            c->mostrar();
            std::cout << " ";
        }
    }

    int tamano() const { return static_cast<int>(cartas.size()); }
};
