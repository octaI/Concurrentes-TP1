
#include "../../include/juego/Mazo.h"

Mazo::Mazo() {
    this->generar();
}

void Mazo::generar(){
    int indice = 0;

    for (int palo = Oro; palo <= Basto; palo++){
        int numero = 1;
        for (numero; numero <= 6; numero++){
            Carta* carta = new Carta(numero, Palo(palo));
            cartas[indice] = carta;
            indice++;
        }

        Siete* siete = new Siete(Palo(palo));
        cartas[indice++] = siete;

        Sota* sota = new Sota(Palo(palo));
        cartas[indice++] = sota;

        Caballo* caballo = new Caballo(Palo(palo));
        cartas[indice++] = caballo;

        Rey* rey = new Rey(Palo(palo));
        cartas[indice++] = rey;
    }
}

Carta* Mazo::tomarCarta() {
    // TODO: Usar stack!
    Carta* ultimaCarta = cartas [cartas.size() - 1];
    cartas.pop_back();
    return ultimaCarta;
}

void Mazo::barajar() {

}

Mazo::~Mazo() {
    //TODO: chequear esto por las dudas.
    for (unsigned i = 0; i < cartas.size(); i++){
        Carta* carta = cartas[i];
        delete carta;
    }
    cartas.clear();
}

int Mazo::cantidadDeCartas() {
    return cartas.size();
}
