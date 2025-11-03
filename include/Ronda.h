#pragma once
#include <vector>

class Jugador;
class Pila;
class Mazo;

class Ronda {
public:
    Ronda(int numJugadores, int maxCartasPorPila = 3);

    // Resetea estado de la ronda (nadie ha tomado pila)
    void iniciarNueva();

    // Marca que un jugador ya tomó pila en esta ronda
    void marcarTomoPila(int idxJugador);

    bool yaTomoPila(int idxJugador) const;
    bool rondaTerminada() const;           // Todos ya tomaron
    int  maxCartasPila() const { return maxCartas; }

private:
    std::vector<bool> tomoPila;
    int maxCartas;
};
