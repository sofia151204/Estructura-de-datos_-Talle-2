#include "juego.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <map>
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
    turnoActual = 0;

    jugadores.reserve(numJugadores);
    for (int i = 0; i < numJugadores; ++i) {
        jugadores.push_back(new Jugador("Jugador " + to_string(i + 1)));
    }
    //pilas.resize(3); // 3 pilas en el centro
    for(int i = 0; i < 3; ++i) {
        pilas.push_back(new Pila()); // agrega una nueva pila
    }

    ronda = new Ronda(numJugadores, /*max cartas por pila*/ 3);
    hayCartaFin = false;
}

Juego::~Juego() {
    delete ronda;
    delete mazo;

    for (Pila* p : pilas) {
        // por seguridad: si quedó alguna carta en la pila, liberarla
        for (Carta* c : p->obtenerCartas()) delete c;
        delete p;
    }
    for (Jugador* j : jugadores) delete j;
}

void Juego::iniciar() {
    cout << "=== COLORETTO (sin comodines, sin +2) ===\n";
    cout << "Regla: max 3 cartas por pila. En tu turno puedes:\n";
    cout << "  1) Robar y colocar en una pila que NO esté llena.\n";
    cout << "  2) Tomar una pila (solo una vez por ronda).\n\n";

    const int numJugadores = (int)jugadores.size();
    int jugadorActual = 0;

    while (true) {
        ronda->iniciarNueva();
        cout << "\n--- NUEVA RONDA ---\n";

        while (!ronda->rondaTerminada()) {
            if (ronda->yaTomoPila(jugadorActual)) {
                jugadorActual = (jugadorActual + 1) % numJugadores;
                continue;
            }

            Jugador* J = jugadores[jugadorActual];

            // mostrar pilas
            cout << "\nTurno de: " << J->getNombre() << "\n";
            cout << "Pilas:\n";
            for (size_t i = 0; i < pilas.size(); ++i) {
                cout << "  Pila " << i+1 << " (" << pilas[i]->tamano() << " cartas): ";
                pilas[i]->mostrar();
            }

            cout << "Elige accion (1=Robar/colocar, 2=Tomar pila): ";
            int accion = leerEnteroSeguro(1, 2);

            if (accion == 1) {
                if (mazo->vacio()) {
                    cout << "El mazo está vacío. Debes tomar una pila.\n";
                } else {
                    Carta* c = mazo->robarCarta();
                    if (c->getColor() == "FIN") {
                        cout << "¡Apareció la carta FIN! Al cerrar esta ronda, se puntúa y termina el juego.\n";
                        hayCartaFin = true;
                        delete c; // FIN no se coloca
                    } else {
                        cout << "Elige pila para colocar la carta (" << c->getColor()
                             << ") [1-" << pilas.size() << "]: ";
                        int idx = leerEnteroSeguro(1, (int)pilas.size());
                        while (pilas[idx-1]->tamano() >= ronda->maxCartasPila()) {
                            cout << "Esa pila ya esta llena (max " << ronda->maxCartasPila()
                                 << "). Elige otra: ";
                            idx = leerEnteroSeguro(1, (int)pilas.size());
                        }
                        pilas[idx-1]->agregarCarta(c);
                    }
                }
            } else {
                cout << "Elige la pila a tomar [1-" << pilas.size() << "]: ";
                int idx = leerEnteroSeguro(1, (int)pilas.size());
                while (pilas[idx-1]->tamano() == 0) {
                    cout << "Esa pila esta vacia, elige otra: ";
                    idx = leerEnteroSeguro(1, (int)pilas.size());
                }

                // mover cartas a la mano del jugador
                auto cartas = pilas[idx-1]->obtenerCartas();
                for (auto* c : cartas) J->recibirCarta(c);
                pilas[idx-1]->vaciar();

                ronda->marcarTomoPila(jugadorActual);
            }

            jugadorActual = (jugadorActual + 1) % numJugadores;
            if (hayCartaFin && ronda->rondaTerminada()) break;
        }

        if (hayCartaFin || mazo->vacio()) {
            cout << "\n*** FIN DE LA PARTIDA ***\n";
            mostrarPuntajesFinales();
            break;
        }
        // Si quieren limpiar pilas entre rondas:
        // for (auto* p : pilas) p->vaciar();
    }
}

void Juego::turno() {
    Jugador* jugador = jugadores[turnoActual];
    cout << "\n--- Turno de " << jugador->getNombre() << " ---\n";

    cout << "Tus cartas: ";
    jugador->mostrarCartas();
    cout << "\nPilas actuales:\n";
    for (size_t i = 0; i < pilas.size(); ++i) {
        cout << "Pila " << (i+1) << " (" << pilas[i]->tamano() << "): ";
        pilas[i]->mostrar();
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
        pilas[p-1]->agregarCarta(carta);   // <-- con '->'
        cout << "Colocada en pila " << p << ".\n";
    }
    else if (opt == 2) {
        cout << "Que pila tomar (1-" << pilas.size() << ")? ";
        int p = leerEnteroSeguro(1, static_cast<int>(pilas.size()));
        auto cartas = pilas[p-1]->obtenerCartas();  // <-- con '->'
        if (cartas.empty()) {
            cout << "Pila vacia. No se puede tomar.\n";
            return;
        }
        for (auto c : cartas) {
            jugador->recibirCarta(c);
        }
        pilas[p-1]->vaciar();   // <-- con '->'
        cout << jugador->getNombre() << " tomo la pila " << p << ".\n";
    }
    else { // opt == 3
        cout << "Mostrando mano y pilas...\n";
        cout << "Tus cartas: ";
        jugador->mostrarCartas();
        cout << "\nPilas actuales:\n";
        for (size_t i = 0; i < pilas.size(); ++i) {
            cout << "Pila " << (i+1) << ": ";
            pilas[i]->mostrar();    // <-- con '->'
            cout << "\n";
        }
    }
}

void Juego::mostrarPuntajesFinales() {
    cout << "\n== PUNTUACION FINAL (Tarjeta CAFE) ==\n";
    cout << left << setw(18) << "Jugador" << right << setw(8) << "Puntos" << "\n";
    cout << "------------------------------\n";

    for (auto* J : jugadores) {
        map<string,int> detalle;
        int total = Puntuacion::puntuar(J->getCartas(), &detalle);

        cout << left << setw(18) << J->getNombre()
             << right << setw(8) << total << "\n";

        for (auto& kv : detalle) {
            cout << "   - " << left << setw(12) << kv.first
                 << right << setw(4) << kv.second << "\n";
        }
    }
    cout << "------------------------------\n";
    cout << "Nota: se suman los 3 colores con mayor cantidad (1,3,6,10,15,21) y se restan los demas (-1..-6).\n";
}

