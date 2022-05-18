//
// Created by Nicolas PIPLARD on 24/04/2022.
//

#ifndef C_PLUS_PLUS_PROJET_ESIEE_2022_GAME_H
#include "../Block/Animal/Animal.h"
#include "../Block/Animal/Type/Mouton/Mouton.h"
#include "../Block/Animal/Type/Loup/Loup.h"
#include "../Block/World/Mineraux.h"
#include "../Block/World/Herbe.h"
#include "../Constants/Constants.h"
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>

using namespace std;
#define C_PLUS_PLUS_PROJET_ESIEE_2022_GAME_H

class Game {

public:

    int size[2];
    int number_loup = 5;
    int number_mouton = 10;
    int number_mineraux = 20;
    vector<Loup> listeLoup;
    vector<Mouton> listeMouton;
    vector<Mineraux> listeMineraux;
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
