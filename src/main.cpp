#include "Mazo.h"
#include "Jugador.h"
#include <iostream>

int main(){
    Jugador ana("Ana");
    Jugador luis("Luis");

    // Simulación mínima: Ana recibe 2 rojas, 1 verde, un +2 y un comodín
    ana.recibirCarta(new CartaColor("Rojo"));
    ana.recibirCarta(new CartaColor("Rojo"));
    ana.recibirCarta(new CartaColor("Verde"));
    ana.recibirCarta(new CartaMasDos());
    ana.recibirCarta(new CartaComodin(false)); // normal

    // Luis recibe 3 azules y 1 amarillo
    luis.recibirCarta(new CartaColor("Azul"));
    luis.recibirCarta(new CartaColor("Azul"));
    luis.recibirCarta(new CartaColor("Azul"));
    luis.recibirCarta(new CartaColor("Amarillo"));

    // Selección de 3 positivos (manual o automática)
    // Manual (índices 0..6): Rojo(0), Verde(2), Morado(5)
    ana.seleccionarPositivos({0,2,5});
    // Auto (elige top-3 por conteo actual)
    luis.seleccionarPositivosAuto();

    // Asigna comodines: manual
    ana.asignarComodin(0); // comodín a Rojo
    // o automático (heurística)
    // ana.asignarComodinesGreedy();

    ana.mostrarZona();
    luis.mostrarZona();

    std::cout << "Puntaje Ana: " << ana.puntajeFinal() << "\n";
    std::cout << "Puntaje Luis: " << luis.puntajeFinal() << "\n";
    return 0;
}
