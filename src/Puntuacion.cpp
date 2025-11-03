#include "Puntuacion.h"
#include <algorithm>

static int clamp6(int n){ return (n < 0 ? 0 : (n > 6 ? 6 : n)); }

int Puntuacion::scorePositivo(int n) {
    // Tabla estándar de Coloretto (tarjeta café)
    static int tabla[] = {0, 1, 3, 6, 10, 15, 21};
    return tabla[clamp6(n)];
}

int Puntuacion::scoreNegativo(int n) {
    // Lineal negativa, tarjeta café
    static int tabla[] = {0, -1, -2, -3, -4, -5, -6};
    return tabla[clamp6(n)];
}

int Puntuacion::puntuar(const std::vector<Carta*>& mano, std::map<std::string,int>* detalle) {
    std::map<std::string,int> conteo;

    // Contar por color (ignoramos "FIN")
    for (auto c : mano) {
        if (!c) continue;
        std::string col = c->getColor();
        if (col == "FIN") continue;
        conteo[col]++;
    }

    // Pasar a vector para ordenar por cantidad
    std::vector<std::pair<std::string,int>> vec(conteo.begin(), conteo.end());
    std::sort(vec.begin(), vec.end(), [](auto& a, auto& b){
        if (a.second != b.second) return a.second > b.second; // desc por cantidad
        return a.first < b.first; // estable por nombre
    });

    int total = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        const auto& [color, n] = vec[i];
        int pts = (i < 3) ? scorePositivo(n) : scoreNegativo(n);
        total += pts;
        if (detalle) (*detalle)[color] = pts;
    }

    if (detalle && vec.empty()) (*detalle)["(sin colores)"] = 0;
    return total;
}
