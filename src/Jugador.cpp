#include "Jugador.h"
#include <iostream>

Jugador::Jugador(const std::string& nombre) : nombre(nombre) {}

Jugador::~Jugador() {
    // liberar cartas que estén en la mano del jugador
    for (auto c : cartas) delete c;
    cartas.clear();
}

void Jugador::recibirCarta(Carta* c) {
    cartas.push_back(c);
}

void Jugador::mostrarCartas() const {
    if (cartas.empty()) {
        std::cout << "[vacío]";
        return;
    }
    for (auto c : cartas) {
        c->mostrar();
        std::cout << " ";
    }
}

std::string Jugador::getNombre() const { return nombre; }
