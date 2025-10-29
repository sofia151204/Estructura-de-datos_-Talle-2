#pragma once
#include <vector>
#include "Jugador.h"
#include "Mazo.h"
#include "Pila.h"

using namespace std;

class Juego {
private:
    vector<Jugador*> jugadores;
    Mazo* mazo;
    vector<Pila> pilas;
    int turnoActual;

public:
    Juego(int numJugadores);
    ~Juego();

    void iniciar();
    void turno(); // controla el turno del jugador actual
};
