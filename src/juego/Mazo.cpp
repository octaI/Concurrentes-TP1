
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

    this->barajar();
}

Carta* Mazo::tomarCarta() {
    Carta* ultimaCarta = cartas->top();
    cartas->pop();

    return ultimaCarta;
}

void Mazo::barajar() {
    std::srand ( unsigned ( std::time(0) ) );

    vector<Carta*> cartasMezcladas [CANT_CARTAS];
    while (!cartas->empty()) {
        cartasMezcladas->push_back( tomarCarta() );
    }
    std::random_shuffle ( cartasMezcladas->begin(), cartasMezcladas->end() );
    for (int i = 0; i < cartasMezcladas->size(); i++) {
        Carta* cartaAAgregar = cartasMezcladas->at(i);
        cartas->push( cartaAAgregar );
    }
}

Mazo::~Mazo() {
    while (!cartas->empty()) {
        delete cartas->top();
        cartas->pop();
    }
    delete cartas;
}

int Mazo::cantidadDeCartas() {
    return cartas->size();
}
