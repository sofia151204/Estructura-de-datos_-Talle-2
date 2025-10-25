// Carta.h
#ifndef CARTA_H
#define CARTA_H
#include <string>

class Carta {
protected:
    std::string tipo;
public:
    Carta(std::string tipo) : tipo(tipo) {}
    virtual ~Carta() {}
    virtual void mostrar() const = 0;
    std::string getTipo() const { return tipo; }
};

#endif
