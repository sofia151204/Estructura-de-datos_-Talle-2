#include "Carta.h"

Carta::Carta(std::string color) : color(color) {}

std::string Carta::getColor() const {
    return color;
}

void Carta::mostrar() const {
    std::cout << "[" << color << "]";
}
