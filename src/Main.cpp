#include <iostream>
#include <assert.h>
#include "../include/juego/Atrevido.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Bienvenidos!" << endl;

    int nroJugadores = atoi ( argv[1] );
    assert ( nroJugadores > 1 );
    Atrevido juego (nroJugadores);

    return 0;
}

