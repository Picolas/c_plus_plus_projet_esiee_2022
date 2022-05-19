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
    int number_mineraux = 10;
    int number_herbe = 10;
    vector<vector<Block>> listeBlock; //  = vector<vector<Block>>(50, vector<Block>(50));
    vector<Loup> listeLoup;
    vector<Mouton> listeMouton;
    vector<Mineraux> listeMineraux;
    vector<Herbe> listeHerbe;
    string state;

    Game(int numberLoup, int numberMouton, int numberMineraux, int numberHerbe, int x, int y);

    Game(int number_loup, int number_mouton, int number_mineraux, int x, int y);

    Game(int x, int y);

    Game();

    void setSize(int x, int y);

    void startGame();

    void gameLoop();

    void addMouton(int nombre);

    void addLoup(int nombre);

    void addMineraux(int nombre);

    void addHerbe(int nombre);

    int * generateCoordonate();

    bool searchInArray(int x, int y);

    string getBlockType(int x, int y);

    void moutonMangeHerbe(int x, int y, Mouton& mouton);

    void loupMangeMouton(int x, int y, Loup& loup);

    void changeHerbeMineraux(int x, int y, Mineraux& mineraux);

    void changeBlockType(int x, int y, Block& mineraux);

    //void initMap();

    void fillMapBlock();

    void rezizeListBlock();

    void showGame() {
        for (int i = 0; i < this->size[0] * 5; ++i) {
            for (int j = 0; j < size[1] * 5; ++j) {

            }
        }
    }
};


#endif //C_PLUS_PLUS_PROJET_ESIEE_2022_GAME_H
