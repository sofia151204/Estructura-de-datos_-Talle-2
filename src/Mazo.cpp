#include "Mazo.h"
#include <iostream>
using namespace std;

Mazo::Mazo() {
    string colores[] = {"rojo", "verde", "azul", "amarillo", "morado", "naranja", "gris"};
    int totalColores = sizeof(colores) / sizeof(colores[0]);

    cantidad = 7 * 9 + 1; // 9 cartas de cada color + 1 fin de juego
    cartas = new Carta*[cantidad];

    int index = 0;
    for (int c = 0; c < totalColores; ++c) {
        for (int i = 0; i < 9; ++i) {
            cartas[index++] = new Carta(colores[c]);
        }
    }
    cartas[index] = new Carta("FIN");

    barajar();
}

void Mazo::barajar() {
    vector<Carta*> temp(cartas, cartas + cantidad);
    random_device rd;
    mt19937 g(rd());
    shuffle(temp.begin(), temp.end(), g);
    for (int i = 0; i < cantidad; ++i)
        cartas[i] = temp[i];
}

Carta* Mazo::robarCarta() {
    if (vacio()) return nullptr;
    return cartas[--cantidad]; // retira la última carta
}

bool Mazo::vacio() const {
    return cantidad <= 0;
}

Mazo::~Mazo() {
    for (int i = 0; i < cantidad; ++i) {
        delete cartas[i];
    }
    delete[] cartas;
    cout << "Mazo destruido correctamente.\n";
}
