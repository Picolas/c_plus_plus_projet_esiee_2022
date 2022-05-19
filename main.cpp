#include <iostream>
#include "Class/Game/Game.h"

int main() {


    Game game(20, 20);

    int * resultCoordonate;
    resultCoordonate = game.generateCoordonate();
    Herbe herbe(resultCoordonate[0], resultCoordonate[1]);
    //this->listeHerbe.push_back(herbe);
    game.listeBlock[resultCoordonate[0]][resultCoordonate[1]] = herbe;

    for (int i = 0; i < game.size[0]; ++i) {
        for (int j = 0; j < game.size[1]; ++j) {
            cout << game.listeBlock[i][j].type << endl;
        }
    }

    return 0;
}
