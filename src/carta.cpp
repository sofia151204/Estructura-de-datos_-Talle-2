#include "Carta.h"
using namespace std;

Carta::Carta(string color) : color(color) {}

string Carta::getColor() const {
    return color;
}

void Carta::mostrar() const {
    cout << "[" << color << "]";
}

string Carta::toString() const {
    return color;
}
