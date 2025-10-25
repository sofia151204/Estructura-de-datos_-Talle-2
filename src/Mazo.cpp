#include "Mazo.h"
#include <iostream> 

Mazo::Mazo() {
    cantidad = 63 + 10 + 3 + 1;
    cartas = new Carta*[cantidad];
    int index = 0;

    std::string colores[7] = {"Rojo", "Azul", "Verde", "Amarillo",
                              "Naranja", "Morado", "Rosa"};
    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 9; ++j)
            cartas[index++] = new CartaColor(colores[i]);

    for (int i = 0; i < 10; ++i)
        cartas[index++] = new CartaMasDos();

    cartas[index++] = new CartaComodin(false);
    cartas[index++] = new CartaComodin(false);
    cartas[index++] = new CartaComodin(true);

    cartas[index++] = new CartaUltimaRonda();
}

void Mazo::mostrarCartas() const {
    for (int i = 0; i < cantidad; ++i) {
        cartas[i]->mostrar();
        if ((i + 1) % 9 == 0) std::cout << "---------------------\n";
    }
}

Mazo::~Mazo() {
    for (int i = 0; i < cantidad; ++i) delete cartas[i];
    delete[] cartas;
}
