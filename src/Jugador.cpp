#include "Jugador.h"
#include <iostream>
using namespace std;

Jugador::Jugador(const string& nombre) : nombre(nombre) {}

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
        cout << "[vacio]";
        return;
    }
    for (auto c : cartas) {
        c->mostrar();
        cout << " ";
    }
}

string Jugador::getNombre() const { return nombre; }
