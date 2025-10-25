#pragma once
#include "Carta.h"
#include <vector>
#include <string>

class Jugador {
private:
    std::string nombre;
    std::vector<Carta*> cartas;

public:
    Jugador(std::string nombre);
    void recibirCarta(Carta* carta);
    void mostrarCartas() const;
    std::string getNombre() const;
};
