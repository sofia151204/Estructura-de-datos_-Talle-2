#include "/Jugador.h"
#include <iostream>

Jugador::Jugador(std::string nombre) : nombre(nombre) {}

void Jugador::recibirCarta(Carta* carta) {
    cartas.push_back(carta);
}

void Jugador::mostrarCartas() const {
    std::cout << nombre << " tiene: ";
    for (auto c : cartas) c->mostrar();
    std::cout << "\n";
}

std::string Jugador::getNombre() const {
    return nombre;
}
