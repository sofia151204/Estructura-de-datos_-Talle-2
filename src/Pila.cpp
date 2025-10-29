#include "Pila.h"
#include <iostream>
using namespace std;

void Pila::agregarCarta(Carta* carta) {
    cartas.push_back(carta);
}

vector<Carta*> Pila::obtenerCartas() const {
    return cartas;
}

void Pila::vaciar() {
    cartas.clear();
}

int Pila::tamano() const {
    return cartas.size();
}

void Pila::mostrar() const {
    cout << "Pila: ";
    for (const auto& carta : cartas) {
        cout << carta->toString() << " ";
    }
    cout << endl;
}

void Pila::ultimaCarta() {
    if (!cartas.empty()) {
        cout << "Última carta en la pila: ";
        cartas.back()->mostrar();
        cout << endl;
    } else {
        cout << "La pila está vacía." << endl;
    }
}