//
// Created by Nicolas PIPLARD on 29/04/2022.
//

#include "Place.h"

bool Place::staticSearchInArray(int x, int y, Game &game) {
    bool canPlaceMouton = true;
    bool canPlaceLoup = true;
    bool canPlaceMineraux = true;

    int number_mouton = game.number_mouton;
    int number_loup = game.number_loup;
    int number_mineraux = game.number_mineraux;
    //Find mouton;
    for (int i = 0; i < number_mouton; ++i) {
        if (game.listeMouton[i].coordonates[0] == x && game.listeMouton[i].coordonates[1] == y) {
            canPlaceMouton = false;
            break;
        }
    }

    //Find loup;
    for (int i = 0; i < number_loup; ++i) {
        if (game.listeLoup[i].coordonates[0] == x && game.listeLoup[i].coordonates[1] == y) {
            canPlaceLoup = false;
            break;
        }
    }

    //Find mineraux;
    for (int i = 0; i < number_mineraux; ++i) {
        if (game.listeMineraux[i].coordonates[0] == x && game.listeMineraux[i].coordonates[1] == y) {
            canPlaceMineraux = false;
            break;
        }
    }

    if (canPlaceMouton && canPlaceLoup  && canPlaceMineraux) {
        return true;
    }

    return false;
}

string Place::getBlockType(int x, int y, Game& game) {
    //Find mouton;
    for (int i = 0; i < game.number_mouton; ++i) {
        if (game.listeMouton[i].coordonates[0] == x && game.listeMouton[i].coordonates[1] == y)
            return MOUTON;
    }

    //Find loup;
    for (int i = 0; i < game.number_loup; ++i) {
        if (game.listeLoup[i].coordonates[0] == x && game.listeLoup[i].coordonates[1] == y)
           return LOUP;
    }

    //Find mineraux;
    for (int i = 0; i < game.number_mineraux; ++i) {
        if (game.listeMineraux[i].coordonates[0] == x && game.listeMineraux[i].coordonates[1] == y)
            return MINERAUX;
    }

    return HERBE;
}



