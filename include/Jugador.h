#pragma once
#include "Carta.h"
#include <vector>
#include <string>
using namespace std;

class Jugador {
private:
    string nombre;
    vector<Carta*> cartas;
public:
    Jugador(const string& nombre);
    ~Jugador(); // destructor que limpia sus cartas
    void recibirCarta(Carta* c);
    void mostrarCartas() const;
    string getNombre() const;

    const std::vector<Carta*>& getCartas() const { return cartas; }
};