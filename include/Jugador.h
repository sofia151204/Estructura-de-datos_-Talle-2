#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "Carta.h"
#include "CartaColor.h"
#include "CartaMasDos.h"
#include "CartaComodin.h"
#include "CartaUltimaRonda.h"

// Mapa fijo de 7 colores
inline int colorIndexFromString(const std::string& c) {
    if (c=="Rojo") return 0;
    if (c=="Azul") return 1;
    if (c=="Verde") return 2;
    if (c=="Amarillo") return 3;
    if (c=="Naranja") return 4;
    if (c=="Morado") return 5;
    if (c=="Rosa") return 6;
    return -1;
}

class Jugador {
    std::string nombre;

    // Zona de juego (memoria dinámica explícita)
    int* conteoColores;  // tamaño 7
    bool* positivos;     // tamaño 7

    // Otras pilas de la zona
    int cartasMasDos;        // +2
    int comodinesNormales;   // 2 posibles
    int comodinDorado;       // 1 posible

    // tabla de puntuación (lado café)
    int puntosColor(int n) const;

public:
    Jugador(const std::string& nombre);
    ~Jugador();

    const std::string& getNombre() const { return nombre; }

    // --- Zona de juego ---
    void recibirCarta(Carta* c);                     // separa por color/+2/comodín
    void mostrarZona() const;                        // imprime estado de la zona

    // --- Selección de 3 positivos ---
    void seleccionarPositivos(const std::vector<int>& indices); // manual (0..6)
    void seleccionarPositivosAuto();                 // automático: top 3 colores

    // --- Comodines ---
    void asignarComodin(int colorIdx, bool dorado=false); // asignación manual
    void asignarComodinesGreedy();                        // asignación “inteligente” simple

    // --- Puntaje final (lado café) ---
    int puntajeFinal() const;
};

#endif
