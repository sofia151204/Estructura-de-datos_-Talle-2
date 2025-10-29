#pragma once
#include "Carta.h"
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

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
