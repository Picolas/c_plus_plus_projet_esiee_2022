#include <iostream>
#include "Class/Game/Game.h"

int main() {


    Game game(12, 12);

    for (Loup loup : game.listeLoup) {
        cout << to_string(loup.coordonates[0]) << ", " << to_string(loup.coordonates[1]) << endl;
    }

    game.showGame();

    return 0;
}
