//
// Created by Nicolas PIPLARD on 24/04/2022.
//

#ifndef C_PLUS_PLUS_PROJET_ESIEE_2022_GAME_H
#include "../Animal/Animal.h"
#include "../Animal/Type/Mouton/Mouton.h"
#include "../Animal/Type/Loup/Loup.h"
#include "../World/Mineraux.h"
#include "../World/Herbe.h"
#include <cstdlib>
#include <string>

using namespace std;
#define C_PLUS_PLUS_PROJET_ESIEE_2022_GAME_H

class Game {

public:

    int size[2];
    int number_loup = 5;
    int number_mouton = 10;
    int number_mineraux = 20;
    Loup *listeLoup;
    Mouton *listeMouton;
    Mineraux *listeMineraux;
    string state;

    Game(int number_loup, int number_mouton, int number_mineraux, int x, int y);

    Game(int x, int y);

    Game();

    void setSize(int x, int y);

    void startGame();

    void gameLoop();

    void addMouton(int nombre);

    void addLoup(int nombre);

    void addMineraux(int nombre);

    int * generateCoordonate();

    bool searchInArray(int x, int y);
};


#endif //C_PLUS_PLUS_PROJET_ESIEE_2022_GAME_H
