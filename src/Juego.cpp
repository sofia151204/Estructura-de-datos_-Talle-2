#include "juego.h"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

static int leerEnteroSeguro(int minVal, int maxVal) { // valida que la entrada sea un entero dentro de rango
    int x;
    while (true) {
        if (!(cin >> x)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida, intente de nuevo: ";
            continue;
        }
        if (x < minVal || x > maxVal) {
            cout << "Valor fuera de rango, intente de nuevo: ";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return x;
    }
}

Juego::Juego(int numJugadores) {
    mazo = new Mazo(); // usa tu Mazo existente
    for (int i = 0; i < numJugadores; ++i) {
        jugadores.push_back(new Jugador("Jugador " + to_string(i + 1)));
    }
    pilas.resize(3); // 3 pilas en el centro
    turnoActual = 0;
    ronda = new Ronda(numJugadores, /*max cartas por pila*/ 3);
    hayCartaFin = false;
}

Juego::~Juego() {
    delete ronda;
    delete mazo;
    for (Jugador* p : jugadores) delete p;
}

void Juego::iniciar() {
    cout << "Iniciando Coloretto clasico (" << jugadores.size() << " jugadores)\n";

    while (!mazo->vacio()) {
        turno();
        // si la carta final fue robada dentro de turno, el mazo->vacio() debería reflejarlo
        turnoActual = (turnoActual + 1) % jugadores.size();
    }

    cout << "\n=== Estado final ===\n";
    for (auto j : jugadores) {
        cout << j->getNombre() << " tiene: ";
        j->mostrarCartas();
        cout << "\n";
    }
    cout << "\nJuego terminado.\n";
}

void Juego::turno() {
    Jugador* jugador = jugadores[turnoActual];
    cout << "\n--- Turno de " << jugador->getNombre() << " ---\n";

    cout << "Tus cartas: ";
    jugador->mostrarCartas();
    cout << "\nPilas actuales:\n";
    for (size_t i = 0; i < pilas.size(); ++i) {
        cout << "Pila " << (i+1) << " (" << pilas[i].tamano() << "): ";
        pilas[i].mostrar();
        cout << "\n";
    }

    cout << "\nOpciones:\n";
    cout << "1) Robar carta y colocar en una pila\n";
    cout << "2) Tomar una pila (y quedarse con sus cartas)\n";
    cout << "3) Mostrar mano-pilas nuevamente\n";
    cout << "Elige (1-3): ";

    int opt = leerEnteroSeguro(1, 3);

    if (opt == 1) {
        Carta* carta = mazo->robarCarta(); 
        if (!carta) {
            cout << "No hay carta para robar.\n";
            return;
        }

        // Detectar carta FIN
        if (carta->getColor() == "FIN") {
            cout << "Carta de Fin de juego revelada!\n";
            delete carta; // liberamos la carta final
            return;
        }

        cout << "Carta robada: ";
        carta->mostrar();
        cout << "\nEn que pila colocarla (1-" << pilas.size() << ")? ";
        int p = leerEnteroSeguro(1, static_cast<int>(pilas.size()));
        pilas[p-1].agregarCarta(carta);
        cout << "Colocada en pila " << p << ".\n";
    }

    else if (opt == 2) {
        cout << "Que pila tomar (1-" << pilas.size() << ")? ";
        int p = leerEnteroSeguro(1, static_cast<int>(pilas.size()));
        auto cartas = pilas[p-1].obtenerCartas();
        if (cartas.empty()) {
            cout << "Pila vacia. No se puede tomar.\n";
            return;
        }
        for (auto c : cartas) {
            jugador->recibirCarta(c);
        }
        pilas[p-1].vaciar();
        cout << jugador->getNombre() << " tomo la pila " << p << ".\n";
    }

    else { // opt == 3
        cout << "Mostrando mano y pilas...\n";
        cout << "Tus cartas: ";
        jugador->mostrarCartas();
        cout << "\nPilas actuales:\n";
        for (size_t i = 0; i < pilas.size(); ++i) {
            cout << "Pila " << (i+1) << ": ";
            pilas[i].mostrar();
            cout << "\n";
        }
    }
}
