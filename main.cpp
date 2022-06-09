#include <iostream>
#include "Class/Game/Game.h"

int main() {

    srand(time(0));
    Game game(12, 12);

    cout << "Appuyez sur entrer pour quitter" << endl;
    cin.ignore();

    return 0;
}
