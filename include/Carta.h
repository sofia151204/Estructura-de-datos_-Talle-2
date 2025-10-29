#pragma once
#include <string>
#include <iostream>
using namespace std;

class Carta {
private:
    string color;

public:
    Carta(string color);
    string getColor() const;
    void mostrar() const;
    string toString() const;

};
