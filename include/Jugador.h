#pragma once
#include "Carta.h"
#include <vector>
#include <string>

class Jugador {
private:
    std::string nombre;
    std::vector<Carta*> cartas;
public:
    Jugador(const std::string& nombre);
    ~Jugador(); // destructor que limpia sus cartas
    void recibirCarta(Carta* c);
    void mostrarCartas() const;
    std::string getNombre() const;
};