#include "../include/juego.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <map>
#include <cctype>
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
    mazo = new Mazo();
    turnoActual = 0;

    jugadores.reserve(numJugadores);
    for (int i = 0; i < numJugadores; ++i) {
        cout << "Ingrese el nombre del jugador " << (i + 1) << ": ";
        string nombre;
        cin >> nombre;
        jugadores.push_back(new Jugador(nombre));
    }

    for (int i = 0; i < 3; ++i)
        pilas.push_back(new Pila());

    pilaBloqueada.assign(pilas.size(), false);

    ronda = new Ronda(numJugadores, 3);
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
    cout << "  1) Robar y colocar en una pila que NO este llena ni bloqueada.\n";
    cout << "  2) Tomar una pila (solo una vez por ronda).\n\n";

    const int numJugadores = (int)jugadores.size();
    int jugadorActual = 0;

    while (true) {
        ronda->iniciarNueva();

        // al arrancar ronda: desbloquear TODAS las pilas
        pilaBloqueada.assign(pilas.size(), false);

        cout << "\n--- NUEVA RONDA ---\n";

        while (!ronda->rondaTerminada()) {

            if (ronda->yaTomoPila(jugadorActual)) {
                jugadorActual = (jugadorActual + 1) % numJugadores;
                continue;
            }

            Jugador* J = jugadores[jugadorActual];

            // Mostrar pilas con estado
            cout << "\nTurno de: " << J->getNombre() << "\n";
            cout << "Pilas:\n";
            for (size_t i = 0; i < pilas.size(); ++i) {
                cout << "  Pila " << i+1 << " (" << pilas[i]->tamano() << " cartas): ";
                pilas[i]->mostrar();
                if (pilaBloqueada[i])                                 cout << "  [BLOQUEADA]";
                else if (pilas[i]->tamano() >= ronda->maxCartasPila()) cout << "  [LLENA]";
                cout << "\n";
            }

            // Decidir si existe al menos UNA pila disponible para robar/colocar
            bool puedeRobar = hayPilaDisponibleParaRobar();
            bool vacias     = todasPilasVacias();

            // Si ya salió FIN, NO se puede robar más en esta ronda
            if (hayCartaFin) puedeRobar = false;

            // Menú según disponibilidad real
            int accion;
            if (vacias && !hayCartaFin) {
                // todas las pilas están vacías → SOLO se puede robar/colocar (si no ha salido FIN)
                cout << "Elige accion (1=Robar/colocar): ";
                accion = 1;
            } else if (!puedeRobar) {
                // no hay ninguna pila válida para colocar (todas llenas/bloqueadas) o ya salió FIN
                cout << "Elige accion (2=Tomar pila): ";
                accion = 2;
            } else {
                // caso normal: ambas opciones disponibles
                cout << "Elige accion (1=Robar/colocar, 2=Tomar pila): ";
                accion = leerEnteroSeguro(1, 2);
            }

            if (accion == 1) {
                if (mazo->vacio()) {
                    cout << "El mazo está vacío. Debes tomar una pila.\n";
                } else {
                    Carta* c = mazo->robarCarta();
                    if (!c) {
                        cout << "No hay carta para robar.\n";
                    } else if (c->esFin()) { // usar helper robusto
                        cout << "¡Apareció la carta FIN! Al cerrar esta ronda, se puntúa y termina el juego.\n";
                        hayCartaFin = true;
                        delete c; // FIN no se coloca
                    } else {
                        // Elegir una pila disponible (no bloqueada y no llena)
                        cout << "Elige pila para colocar la carta (" << c->getColor()
                             << ") [1-" << pilas.size() << "]: ";

                        int idx = leerEnteroSeguro(1, (int)pilas.size());
                        while (!pilaDisponible(idx - 1)) {
                            cout << "Esa pila no esta disponible ("
                                 << (pilaBloqueada[idx-1] ? "bloqueada" : "llena")
                                 << "). Elige otra: ";
                            idx = leerEnteroSeguro(1, (int)pilas.size());
                        }

                        pilas[idx-1]->agregarCarta(c);
                    }
                }
            } else { // accion == 2
                // No permitir tomar una pila ya bloqueada
                cout << "Elige la pila a tomar [1-" << pilas.size() << "]: ";
                int idx = leerEnteroSeguro(1, (int)pilas.size());

                while (pilaBloqueada[idx-1]) {
                    cout << "Esa pila ya fue tomada y esta BLOQUEADA. Elige otra: ";
                    idx = leerEnteroSeguro(1, (int)pilas.size());
                }
                while (pilas[idx-1]->tamano() == 0) {
                    cout << "Esa pila esta vacia, elige otra: ";
                    idx = leerEnteroSeguro(1, (int)pilas.size());
                }

                // mover cartas a la mano del jugador
                auto cartas = pilas[idx-1]->obtenerCartas();
                for (auto* c : cartas) J->recibirCarta(c);
                pilas[idx-1]->vaciar();

                // Bloquear esa pila hasta la nueva ronda
                pilaBloqueada[idx-1] = true;

                // marcar que este jugador ya tomó pila
                ronda->marcarTomoPila(jugadorActual);
            }

            // siguiente jugador
            jugadorActual = (jugadorActual + 1) % numJugadores;
        }

        // === RONDA CERRADA AQUÍ ===

        // Si se reveló FIN, NO arranques otra ronda: termina y puntúa
        if (hayCartaFin) {
            cout << "\n*** FIN DE LA PARTIDA ***\n";
            mostrarPuntajesFinales();
            return; // salir de iniciar()
        }

        // 🔚 Si no hubo FIN pero el mazo se agotó al cerrar la ronda, también termina
        if (mazo->vacio()) {
            cout << "\nEl mazo se ha agotado. La partida ha terminado.\n";
            mostrarPuntajesFinales();
            return; // salir de iniciar()
        }

        // Si quieres limpiar pilas entre rondas, descomenta:
        // for (auto* p : pilas) p->vaciar();
    }

    // Guard clause: si por algún motivo saliéramos del while(true)
    cout << "\n*** FIN DE LA PARTIDA (salida inesperada del bucle) ***\n";
    mostrarPuntajesFinales();
}

void Juego::turno() {
    // (lo de turno() puede quedar como UI alternativa; no es usado en iniciar())
    Jugador* jugador = jugadores[turnoActual];
    cout << "\n--- Turno de " << jugador->getNombre() << " ---\n";

    cout << "Tus cartas: ";
    jugador->mostrarCartas();

    cout << "\nPilas actuales:\n";
    for (size_t i = 0; i < pilas.size(); ++i) {
        cout << "Pila " << (i+1)
             << " (" << pilas[i]->tamano() << "): ";
        pilas[i]->mostrar();
        if (pilaBloqueada[i])       cout << "  [BLOQUEADA]";
        else if (pilas[i]->tamano() >= ronda->maxCartasPila()) cout << "  [LLENA]";
        cout << "\n";
    }

    const bool puedeRobar = hayPilaDisponibleParaRobar();

    cout << "\nOpciones:\n";
    if (puedeRobar)
        cout << "1) Robar carta y colocar en una pila\n";
    cout << "2) Tomar una pila (y quedarse con sus cartas)\n";
    cout << "3) Mostrar mano-pilas nuevamente\n";
    cout << "Elige (" << (puedeRobar ? "1-3" : "2-3") << "): ";

    int minOpt = (puedeRobar ? 1 : 2);
    int opt = leerEnteroSeguro(minOpt, 3);

    if (opt == 1 && puedeRobar) {
        Carta* carta = mazo->robarCarta();
        if (!carta) {
            cout << "No hay carta para robar.\n";
            return;
        }

        if (carta->esFin()) {
            cout << "Carta de Fin de juego revelada!\n";
            delete carta; // FIN no se coloca
            return;
        }

        cout << "Carta robada: ";
        carta->mostrar();
        cout << "\n¿En qué pila colocarla (1-" << pilas.size() << ")? ";

        int p = leerEnteroSeguro(1, static_cast<int>(pilas.size()));
        while (!pilaDisponible(p-1)) {
            cout << "Esa pila no está disponible ("
                 << (pilaBloqueada[p-1] ? "bloqueada" : "llena")
                 << "). Elige otra: ";
            p = leerEnteroSeguro(1, static_cast<int>(pilas.size()));
        }

        pilas[p-1]->agregarCarta(carta);
        cout << "Colocada en pila " << p << ".\n";
    }
    else if (opt == 2) {
        cout << "¿Qué pila tomar (1-" << pilas.size() << ")? ";
        int p = leerEnteroSeguro(1, static_cast<int>(pilas.size()));

        // no se puede tomar una pila ya bloqueada (ya fue tomada)
        while (pilaBloqueada[p-1]) {
            cout << "Esa pila ya fue tomada y está bloqueada. Elige otra: ";
            p = leerEnteroSeguro(1, static_cast<int>(pilas.size()));
        }

        auto cartas = pilas[p-1]->obtenerCartas();
        if (cartas.empty()) {
            cout << "Pila vacía. No se puede tomar.\n";
            return;
        }

        for (auto* c : cartas) jugador->recibirCarta(c);
        pilas[p-1]->vaciar();

        // bloquear esa pila hasta la siguiente ronda
        pilaBloqueada[p-1] = true;

        cout << jugador->getNombre() << " tomó la pila " << p << " (ahora BLOQUEADA).\n";
    }
    else { // opt == 3
        cout << "Mostrando mano y pilas...\n";
        cout << "Tus cartas: ";
        jugador->mostrarCartas();
        cout << "\nPilas actuales:\n";
        for (size_t i = 0; i < pilas.size(); ++i) {
            cout << "Pila " << (i+1) << ": ";
            pilas[i]->mostrar();
            if (pilaBloqueada[i])       cout << "  [BLOQUEADA]";
            else if (pilas[i]->tamano() >= ronda->maxCartasPila()) cout << "  [LLENA]";
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

bool Juego::pilaDisponible(int idx) const {
    return !pilaBloqueada[idx] && (pilas[idx]->tamano() < ronda->maxCartasPila());
}

bool Juego::hayPilaDisponibleParaRobar() const {
    for (size_t i = 0; i < pilas.size(); ++i)
        if (pilaDisponible((int)i)) return true;
    return false;
}

bool Juego::todasPilasVacias() const {
    for (const auto* p : pilas) {
        if (p->tamano() > 0) return false;
    }
    return true;
}
