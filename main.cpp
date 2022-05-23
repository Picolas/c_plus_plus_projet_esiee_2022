#include <iostream>
#include "Class/Game/Game.h"

int main() {


    Game game(12, 12);


    for (Mouton mouton : game.listeMouton) {
        cout << "[" << to_string(mouton.coordonates[0] + 1) << game.intToLetter(mouton.coordonates[1]) << "]" << endl;
    }

    game.showEvents();

    game.showGame();

    game.loupMangeMouton(game.listeMouton[0], game.listeLoup[0]);
    game.loupMangeMouton(game.listeMouton[1], game.listeLoup[2]);
    game.loupMangeMouton(game.listeMouton[6], game.listeLoup[3]);

    game.showEvents();

    game.showGame();

    for (Mouton mouton : game.listeMouton) {
        cout << "[" << to_string(mouton.coordonates[0] + 1) << game.intToLetter(mouton.coordonates[1]) << "]" << endl;
    }


    game.showGame();
    return 0;
}
