
#include "../../include/juego/Mazo.h"

Mazo::Mazo() {
    this->generar();
}

void Mazo::generar() {
    int indice = 0;
    cartas = new stack<Carta*>();

    for (int palo = Oro; palo <= Basto; palo++) {
        int numero = 1;
        for (numero; numero <= 6; numero++) {
            Carta *carta = new Carta(numero, Palo(palo));
            cartas->push(carta);
            indice++;
        }

        Carta* siete = new Carta(7, Palo(palo));
        cartas->push(siete);

        Carta *sota = new Carta(10, Palo(palo));
        cartas->push(sota);

        Carta *caballo = new Carta(11, Palo(palo));
        cartas->push(caballo);

        Carta *rey = new Carta(12, Palo(palo));
        cartas->push(rey);
    }
}

Carta* Mazo::tomarCarta() {
    cout << "Mazo.cpp: Cartas en el mazo ANTES de tomar carta: " << this->cantidadDeCartas() << endl;
    Carta* ultimaCarta = cartas->top();
    cartas->pop();
    cout << "Mazo.cpp: Cartas en el mazo DESPUES de tomar carta: " << this->cantidadDeCartas() << endl;

    return ultimaCarta;
}

void Mazo::barajar() {
    //TODO: mezclar el mazo de alguna forma, sino siempre se reparte lo mismo.
}

Mazo::~Mazo() {
    //TODO: se esta perdiendo memoria por todos lados
}

int Mazo::cantidadDeCartas() {
    return cartas->size();
}
