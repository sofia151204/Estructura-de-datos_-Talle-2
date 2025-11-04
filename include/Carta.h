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

    bool esFin() const {
        std::string c = getColor();
        for (auto &ch : c) ch = std::toupper(static_cast<unsigned char>(ch));
        return c == "FIN";
    }

};
