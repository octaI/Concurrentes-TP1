
#ifndef CONCURRENTES_TP1_PARSER_H
#define CONCURRENTES_TP1_PARSER_H


class Parser {

public:
    Parser();
    ~Parser();
    Parser(const Parser& origen);
    Parser& operator= (const Parser& origen);

    int leerCantidadDeJugadores ();
};


#endif //CONCURRENTES_TP1_PARSER_H
