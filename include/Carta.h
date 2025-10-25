#pragma once
#include <string>
#include <iostream>

class Carta {
private:
    std::string color;

public:
    Carta(std::string color);
    std::string getColor() const;
    void mostrar() const;
};
