#include <iostream>
#include "Class/Game/Game.h"

int main() {


    Game game(50, 50);

    game.addLoup(10);

    game.listeLoup;

    for (Loup loup : game.listeLoup) {
        cout << loup.coordonates[0] << endl;
    }

    return 0;
}
