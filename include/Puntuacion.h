#pragma once
#include <vector>
#include <string>
#include <map>
#include "Carta.h"

class Puntuacion {
public:
    // Aplica tarjeta café: 3 colores con puntaje positivo, resto negativo.
    // Regresa el puntaje total y opcionalmente llena el detalle por color.
    static int puntuar(const std::vector<Carta*>& mano, std::map<std::string,int>* detalle = nullptr);

private:
    static int scorePositivo(int n); 
    static int scoreNegativo(int n); 
    
};
