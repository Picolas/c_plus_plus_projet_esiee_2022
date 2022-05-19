#include <iostream>
#include "Class/Game/Game.h"

int main() {


    Game game(50, 50);


    game.listeBlock;

    cout << typeid(game).name();

    for (int i = 0; i < game.size[0]; ++i) {
        for (int j = 0; j < game.size[1]; ++j) {
            cout << game.listeBlock[i][j].type << endl;
        }
    }

    return 0;
}
