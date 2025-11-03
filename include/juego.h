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
    Mazo* mazo;
    std::vector<Pila*> pilas;
    std::vector<Jugador*> jugadores;
    int turnoActual;

    Ronda* ronda;          // controla estado de la ronda (quién ya tomó)
    bool hayCartaFin;      // si salió la carta FIN

    void mostrarPuntajesFinales();

public:
    explicit Juego(int numJugadores);
    ~Juego();

    void iniciar();
    void turno(); // controla el turno del jugador actual
};
