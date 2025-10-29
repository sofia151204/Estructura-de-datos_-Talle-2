#pragma once
#include <vector>
#include "Jugador.h"
#include "Mazo.h"
#include "Pila.h"

class Juego {
private:
    std::vector<Jugador*> jugadores;
    Mazo* mazo;
    std::vector<Pila> pilas;
    int turnoActual;

public:
    Juego(int numJugadores);
    ~Juego();

    void iniciar();
    void turno(); // controla el turno del jugador actual
};
