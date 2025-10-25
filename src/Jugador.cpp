#include "Jugador.h"

Jugador::Jugador(const std::string& nombre)
: nombre(nombre),
  conteoColores(new int[7]),
  positivos(new bool[7]),
  cartasMasDos(0),
  comodinesNormales(0),
  comodinDorado(0)
{
    for (int i=0;i<7;++i){ conteoColores[i]=0; positivos[i]=false; }
}

Jugador::~Jugador(){
    delete[] conteoColores;
    delete[] positivos;
}


int Jugador::puntosColor(int n) const {
    if (n<=0) return 0;
    if (n==1) return 1;
    if (n==2) return 3;
    if (n==3) return 6;
    if (n==4) return 10;
    if (n==5) return 15;
    return 21;
}

void Jugador::recibirCarta(Carta* c){
   
    if (auto cc = dynamic_cast<CartaColor*>(c)){
        int idx = colorIndexFromString(cc->getColor());
        if (idx>=0) conteoColores[idx] += 1;
    } else if (dynamic_cast<CartaMasDos*>(c)){
        cartasMasDos += 1;
    } else if (auto comodin = dynamic_cast<CartaComodin*>(c)){
       
        if (comodin->getTipo()=="Comodín Dorado") comodinDorado += 1;
        else comodinesNormales += 1;
    } else {
       
    }
}

void Jugador::mostrarZona() const{
    static const char* N[7] = {"Rojo","Azul","Verde","Amarillo","Naranja","Morado","Rosa"};
    std::cout << "=== Zona de " << nombre << " ===\n";
    for (int i=0;i<7;++i){
        std::cout << N[i] << ": " << conteoColores[i]
                  << (positivos[i]?" (positivo)":" (negativo)") << "\n";
    }
    std::cout << "+2: " << cartasMasDos
              << " | Comodines: " << comodinesNormales
              << " | Dorado: " << comodinDorado << "\n";
}

void Jugador::seleccionarPositivos(const std::vector<int>& indices){
    if ((int)indices.size()!=3) throw std::runtime_error("Debes elegir exactamente 3 colores.");
    bool seen[7]={false,false,false,false,false,false,false};
    for (int idx: indices){
        if (idx<0 || idx>6) throw std::runtime_error("Índice de color inválido (0..6).");
        if (seen[idx]) throw std::runtime_error("Color repetido en la selección.");
        seen[idx]=true;
    }
    for (int i=0;i<7;++i) positivos[i]=seen[i];
}


void Jugador::seleccionarPositivosAuto(){
    std::vector<std::pair<int,int>> v; 
    v.reserve(7);
    for (int i=0;i<7;++i) v.push_back({conteoColores[i], i});
    std::sort(v.begin(), v.end(), [](auto& a, auto& b){ return a.first>b.first; });
    bool mark[7]={false,false,false,false,false,false,false};
    for (int k=0;k<3;++k) mark[v[k].second]=true;
    for (int i=0;i<7;++i) positivos[i]=mark[i];
}

void Jugador::asignarComodin(int colorIdx, bool dorado){
    if (colorIdx<0 || colorIdx>6) throw std::runtime_error("Índice de color inválido (0..6).");
    if (dorado){
        if (comodinDorado<=0) throw std::runtime_error("No tienes comodín dorado disponible.");
        conteoColores[colorIdx] += 1;
        comodinDorado -= 1;
    } else {
        if (comodinesNormales<=0) throw std::runtime_error("No tienes comodines normales disponibles.");
        conteoColores[colorIdx] += 1;
        comodinesNormales -= 1;
    }
}


void Jugador::asignarComodinesGreedy(){
    auto delta = [&](int count){
     
        return puntosColor(count+1) - puntosColor(count);
    };

    int total = comodinesNormales + comodinDorado;
    while (total>0){
        int bestIdx = 0;
        int bestGain = -1;
        for (int i=0;i<7;++i){
            int gain = delta(conteoColores[i]);
            
            if (positivos[i]) gain += 1;
            if (gain>bestGain){
                bestGain=gain;
                bestIdx=i;
            }
        }
        conteoColores[bestIdx] += 1;
        total--;
    }

    comodinDorado = 0;
    comodinesNormales = 0;
}

int Jugador::puntajeFinal() const{
    int total = 0;
    for (int i=0;i<7;++i){
        int pts = puntosColor(conteoColores[i]);
        total += positivos[i] ? pts : -pts;
    }
    total += cartasMasDos * 2;
    return total;
}
