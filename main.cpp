#include <iostream>
#include "Class/Game/Game.h"

int main() {


    Game game(12, 12);

    for (Mouton mouton : game.listeMouton) {
        cout << to_string(mouton.coordonates[0]) << ", " << to_string(mouton.coordonates[1]) << endl;
    }

    game.loupMangeMouton(game.listeMouton[0], game.listeLoup[0]);
    game.loupMangeMouton(game.listeMouton[1], game.listeLoup[2]);
    game.loupMangeMouton(game.listeMouton[6], game.listeLoup[3]);

    cout << "Après :" << endl;
    /*
     for (Loup loup : game.listeLoup) {
        cout << to_string(loup.coordonates[0]) << ", " << to_string(loup.coordonates[1]) << endl;
    }
     */

    for (Mouton mouton : game.listeMouton) {
        cout << to_string(mouton.coordonates[0]) << ", " << to_string(mouton.coordonates[1]) << endl;
    }

    game.showEvents();

    game.showGame();

    return 0;
}
