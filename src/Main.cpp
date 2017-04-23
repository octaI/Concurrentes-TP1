#include <iostream>
#include "../include/logger/Logger.h"

using namespace std;

int main() {
    cout << "Bienvenido!" << endl;

    Logger :: getInstance() -> debug("Main", "Testing logger!");

    return 0;
}

