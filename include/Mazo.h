#pragma once
#include "Carta.h"
#include <vector>
#include <random>
#include <algorithm>

class Mazo {
private:
    Carta** cartas; 
    int cantidad;

public:
    Mazo();
    void barajar();
    Carta* robarCarta();
    bool vacio() const;
    ~Mazo();
};
