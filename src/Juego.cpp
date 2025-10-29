#include "Juego.h"
#include <iostream>
#include <limits>

Juego::Juego(int numJugadores) {
    mazo = new Mazo(); // usa tu constructor existente
    for (int i = 0; i < numJugadores; ++i) {
        jugadores.push_back(new Jugador("Jugador " + std::to_string(i + 1)));
    }
    pilas.resize(3); // tres pilas en el centro
    turnoActual = 0;
}

Juego::~Juego() {
    // liberar mazo
    delete mazo;
    // liberar jugadores y las cartas que tengan
    for (auto p : jugadores) delete p;
}

static int leerEnteroSeguro(int minVal, int maxVal) {
    int x;
    while (true) {
        if (!(std::cin >> x)) {
            // limpiar error y descartar la línea
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida, intente de nuevo: ";
            continue;
        }
        if (x < minVal || x > maxVal) {
            std::cout << "Valor fuera de rango, intente de nuevo: ";
            continue;
        }
        // limpiar resto de la línea
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return x;
    }
}

void Juego::iniciar() {
    std::cout << "🎮 Iniciando Coloretto clásico (" << jugadores.size() << " jugadores)\n";

    bool terminado = false;
    while (!mazo->vacio() && !terminado) {
        turno();

        // si la carta que se robó en turno fue FIN, tu lógica de Mazo debe devolverla y el juego terminará
        // si implementaste robarCarta() devolviendo nullptr cuando se encontró FIN y se eliminó, ajustar según tu Mazo.
        turnoActual = (turnoActual + 1) % jugadores.size();
    }

    std::cout << "\n=== Estado final ===\n";
    for (auto j : jugadores) j->mostrarCartas();
    std::cout << "\nJuego terminado.\n";
}

void Juego::turno() {
    Jugador* jugador = jugadores[turnoActual];
    std::cout << "\n--- Turno de " << jugador->getNombre() << " ---\n";

    std::cout << "Tus cartas: ";
    jugador->mostrarCartas();
    std::cout << "\nPilas actuales:\n";
    for (size_t i = 0; i < pilas.size(); ++i) {
        std::cout << "Pila " << (i+1) << " (" << pilas[i].tamano() << "): ";
        pilas[i].mostrar();
        std::cout << "\n";
    }

    std::cout << "\nOpciones:\n";
    std::cout << "1) Robar carta y colocar en una pila\n";
    std::cout << "2) Tomar una pila (y pasar turno)\n";
    std::cout << "3) Mostrar mano/pilas nuevamente\n";
    std::cout << "Elige (1-3): ";

    int opt = leerEnteroSeguro(1, 3);

    if (opt == 1) {
        Carta* carta = mazo->robarCarta(); // nombre del método según tu Mazo
        if (!carta) {
            std::cout << "No hay carta para robar (mazo vacío o carta FIN manejada internamente).\n";
            return;
        }

        // si es carta FIN, asumimos que carta->getColor() == "FIN"
        if (carta->getColor() == "FIN") {
            std::cout << "Carta de Fin de juego revelada!\n";
            // liberamos la carta final
            delete carta;
            // Forzamos terminar el mazo: vaciado o marcar terminado (Aquí simplemente dejamos que el bucle principal vea mazo->vacio())
            return;
        }

        std::cout << "Carta robada: ";
        carta->mostrar();
        std::cout << "\nEn qué pila colocarla (1-" << pilas.size() << ")? ";
        int p = leerEnteroSeguro(1, static_cast<int>(pilas.size()));
        pilas[p-1].agregarCarta(carta);
        std::cout << "Colocada en pila " << p << ".\n";
    }
    else if (opt == 2) {
        std::cout << "Qué pila tomar (1-" << pilas.size() << ")? ";
        int p = leerEnteroSeguro(1, static_cast<int>(pilas.size()));
        // transferir cartas a jugador
        auto cartas = pilas[p-1].obtenerCartas();
        if (cartas.empty()) {
            std::cout << "Pila vacía. No se puede tomar.\n";
            return;
        }
        for (auto c : cartas) {
            jugador->recibirCarta(c);
        }
        // vaciamos la pila (no borramos punteros, pues fueron transferidos)
        pilas[p-1].vaciar();
        std::cout << jugador->getNombre() << " tomo la pila " << p << ".\n";
    }
    else {
        // mostrar de nuevo
        std::cout << "Mostrando mano y pilas...\n";
        std::cout << "Tus cartas: ";
        jugador->mostrarCartas();
        std::cout << "\nPilas actuales:\n";
        for (size_t i = 0; i < pilas.size(); ++i) {
            std::cout << "Pila " << (i+1) << ": ";
            pilas[i].mostrar();
            std::cout << "\n";
        }
    }
}
