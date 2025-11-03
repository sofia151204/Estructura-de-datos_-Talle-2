#pragma once
#include <vector>
#include "Jugador.h"
#include "Mazo.h"
#include "Pila.h"
#include "Ronda.h"
#include "Puntuacion.h"

using namespace std;

class Juego {
private:
    Ronda* ronda;          // controla estado de la ronda (quién ya tomó)
    bool hayCartaFin;      // si salió la carta FIN
    void mostrarPuntajesFinales();
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
