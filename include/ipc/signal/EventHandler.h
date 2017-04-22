
#ifndef CONCURRENTES_TP1_EVENTHANDLER_H
#define CONCURRENTES_TP1_EVENTHANDLER_H


class EventHandler {

public:
    virtual int handleSignal ( int signum ) = 0;
    virtual ~EventHandler () {};

};


#endif //CONCURRENTES_TP1_EVENTHANDLER_H
