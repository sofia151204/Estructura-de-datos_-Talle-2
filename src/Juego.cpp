#include "/Juego.h"
#include <iostream>

Juego::Juego(int numJugadores) {
    mazo = new Mazo();
    for (int i = 0; i < numJugadores; ++i) {
        jugadores.push_back(new Jugador("Jugador " + std::to_string(i + 1)));
    }
}

void Juego::iniciar() {
    std::cout << "🎮 Iniciando Coloretto clásico (" << jugadores.size() << " jugadores)\n\n";
    
    bool fin = false;
    int turno = 0;
    while (!mazo->vacio() && !fin) {
        Carta* carta = mazo->robarCarta();
        if (carta->getColor() == "FIN") {
            std::cout << "🚩 ¡Carta de Fin de juego revelada!\n";
            fin = true;
            delete carta;
        } else {
            jugadores[turno]->recibirCarta(carta);
            std::cout << jugadores[turno]->getNombre() << " roba ";
            carta->mostrar();
            std::cout << "\n";
        }
        turno = (turno + 1) % jugadores.size();
    }

    std::cout << "\n=== Estado final ===\n";
    for (auto j : jugadores) j->mostrarCartas();
}

Juego::~Juego() {
    delete mazo;
    for (auto j : jugadores) delete j;
    std::cout << "Juego terminado correctamente.\n";
}
