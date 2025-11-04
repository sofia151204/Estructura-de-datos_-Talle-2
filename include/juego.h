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
    std::vector<bool> pilaBloqueada;
    std::vector<Pila*> pilas;
    std::vector<Jugador*> jugadores;
    int turnoActual;

    Ronda* ronda;          // controla estado de la ronda (quién ya tomó)
    bool hayCartaFin;      // si salió la carta FIN

    //vector<bool> pilaBloqueada;

    void mostrarPuntajesFinales();
    bool menuFinPartida();          // menú al terminar (nueva partida / salir)
    void resetPartida();

    bool hayPilaDisponibleParaRobar() const;
    bool pilaDisponible(int idx) const;
    bool todasPilasVacias() const;

public:
    explicit Juego(int numJugadores);
    ~Juego();

    void iniciar();
    void turno(); // controla el turno del jugador actual
};
