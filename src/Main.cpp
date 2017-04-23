#include <iostream>
#include "../include/logger/Logger.h"

using namespace std;

int main() {
    cout << "Bienvenido!" << endl;

    Logger :: getInstance() -> debug("Testing logger!");

    return 0;
}

