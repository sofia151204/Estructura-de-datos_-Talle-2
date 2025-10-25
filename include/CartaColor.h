// CartaColor.h
#ifndef CARTA_COLOR_H
#define CARTA_COLOR_H

#include "Carta.h"
#include <iostream>  

class CartaColor : public Carta {
    std::string color;
public:
    CartaColor(std::string color) : Carta("Color"), color(color) {}
    void mostrar() const override {
        std::cout << "Carta de color: " << color << std::endl;
  
    }
    
    std::string getColor() const { return color; }
 

};

#endif
