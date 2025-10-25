#pragma once
#include "Mazo.h"
#include "Jugador.h"
#include <vector>

class Juego {
private:
    std::vector<Jugador*> jugadores;
    Mazo* mazo;

public:
    Juego(int numJugadores);
    void iniciar();
    ~Juego();
};
