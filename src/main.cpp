#include "Mazo.h"
#include "Jugador.h"
#include <iostream>

int main(){
    Jugador ana("Ana");
    Jugador luis("Luis");

    ana.recibirCarta(new CartaColor("Rojo"));
    ana.recibirCarta(new CartaColor("Rojo"));
    ana.recibirCarta(new CartaColor("Verde"));
    ana.recibirCarta(new CartaMasDos());
    ana.recibirCarta(new CartaComodin(false));

    luis.recibirCarta(new CartaColor("Azul"));
    luis.recibirCarta(new CartaColor("Azul"));
    luis.recibirCarta(new CartaColor("Azul"));
    luis.recibirCarta(new CartaColor("Amarillo"));

    ana.seleccionarPositivos({0,2,5});
  
    luis.seleccionarPositivosAuto();

    ana.asignarComodin(0); 
   

    ana.mostrarZona();
    luis.mostrarZona();

    std::cout << "Puntaje Ana: " << ana.puntajeFinal() << "\n";
    std::cout << "Puntaje Luis: " << luis.puntajeFinal() << "\n";
    return 0;
}
