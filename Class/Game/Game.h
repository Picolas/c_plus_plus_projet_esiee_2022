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
#include "../Events/Evenements.h"
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>
#include <iostream>


using namespace std;
#define C_PLUS_PLUS_PROJET_ESIEE_2022_GAME_H

class Game {

public:

    int size[2];
    int tiret_space = TIRETS;
    int number_loup = 5;
    int number_mouton = 20;
    int number_mineraux = 0;
    int number_herbe = 50;
    //vector<vector<Block*>> listeBlock; //  = vector<vector<Block>>(50, vector<Block>(50));
    vector<Loup> listeLoup;
    vector<Mouton> listeMouton;
    vector<Mineraux> listeMineraux;
    vector<Herbe> listeHerbe;
    vector<Evenements> listeEvenements;
    string state;
    int tour = 0;

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

    void moutonMangeHerbe(Herbe& herbe, Mouton& mouton);

    void loupMangeMouton(Mouton& mouton, Loup& loup);

    void changerMinerauxEnHerbe();

    void killMouton(Mouton& mouton, string type);

    void killLoup(Loup& loup, string type);

    void showGame();

    string linePlusMoins();

    string firstLine();

    string secondLine();

    string letterLine();

    char intToLetter(int value);

    void showEvents();

    void checkDieMouton();

    void checkDieLoup();

    void removeFaimAndVie();

    void bestMoveMouton();

    void bestMoveLoup();

    int numberNotSupOrMinOne(int number);

    int numberNotOutOfBound(int number, int size);

    void setShowGameDimansions();

    Herbe getHerbe(int x, int y);

    void randomMoveMouton();

    void randomMoveLoup();

    int getIndexMouton(Mouton& mouton);

    int getIndexLoup(Loup& loup);

    void showNumberLife();

    int getIndexMineraux(Mineraux& mineraux);

    int getIndexHerbe(Herbe& herbe);

    void checkEndGame();

    void reproductionMouton();

    bool canReproductedMouton(Mouton& firstMouton, Mouton& secondMouton);

    bool canReproductedLoup(Loup& firstLoup, Loup& secondLoup);

    Mouton getMouton(int x, int y);

    Loup getLoup(int x, int y);

    void endReproductionMouton();

    void endReproductionLoup();

    void reproductionLoup();

    void incrementTour();
};


#endif //C_PLUS_PLUS_PROJET_ESIEE_2022_GAME_H
