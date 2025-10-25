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

    int* conteoColores;  
    bool* positivos;     

    int cartasMasDos;       
    int comodinesNormales;   
    int comodinDorado;       

    int puntosColor(int n) const;

public:
    Jugador(const std::string& nombre);
    ~Jugador();

    const std::string& getNombre() const { return nombre; }
   
    void recibirCarta(Carta* c);                     
    void mostrarZona() const;     

    void seleccionarPositivos(const std::vector<int>& indices);
    void seleccionarPositivosAuto();                 

    void asignarComodin(int colorIdx, bool dorado=false);
    void asignarComodinesGreedy();                        

    int puntajeFinal() const;
};

#endif
