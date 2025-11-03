#include "Ronda.h"
#include <algorithm>

Ronda::Ronda(int numJugadores, int maxCartasPorPila)
: tomoPila(numJugadores, false), maxCartas(maxCartasPorPila) {}

void Ronda::iniciarNueva() {
    std::fill(tomoPila.begin(), tomoPila.end(), false);
}

void Ronda::marcarTomoPila(int idxJugador) {
    if (idxJugador >= 0 && idxJugador < (int)tomoPila.size()) {
        tomoPila[idxJugador] = true;
    }
}

bool Ronda::yaTomoPila(int idxJugador) const {
    if (idxJugador < 0 || idxJugador >= (int)tomoPila.size()) return false;
    return tomoPila[idxJugador];
}

bool Ronda::rondaTerminada() const {
    for (bool x : tomoPila) if (!x) return false;
    return !tomoPila.empty();
}
