//
// Created by Nicolas PIPLARD on 24/04/2022.
//

#include "Game.h"

Game::Game(int number_loup, int number_mouton, int number_mineraux, int x, int y): number_loup(number_loup), number_mouton(number_mouton), number_mineraux(number_mineraux){
    this->setSize(x, y);
    this->listeLoup = new Loup[number_loup];
    this->listeMouton = new Mouton[number_mouton];
    this->listeMineraux = new Mineraux[number_mineraux];
}

void Game::setSize(int x, int y) {
    this->size[0] = x;
    this->size[1] = y;
}

void Game::startGame() {
    this->state = "started";
}


void Game::gameLoop() {
    while(this->state == "started") {

    }
}

void Game::addLoup(int nombre) {
    int * resultCoordonate;
    for (int i = 0; i < nombre; ++i) {
        resultCoordonate = generateCoordonate();

        Loup * loup = new Loup(resultCoordonate[0], resultCoordonate[1]);

        this->listeLoup[i].coordonates[0] = loup->coordonates[0];
        this->listeLoup[i].coordonates[1] = loup->coordonates[1];
        this->listeLoup[i].vie = loup->vie;
        this->listeLoup[i].faim = loup->faim;
    }
}

void Game::addMouton(int nombre) {
    int * resultCoordonate;
    for (int i = 0; i < nombre; ++i) {
        resultCoordonate = generateCoordonate();

        Mouton * mouton = new Mouton(resultCoordonate[0], resultCoordonate[1]);

        this->listeMouton[i].coordonates[0] = mouton->coordonates[0];
        this->listeMouton[i].coordonates[1] = mouton->coordonates[1];
        this->listeMouton[i].vie = mouton->vie;
        this->listeMouton[i].faim = mouton->faim;
    }
}

void Game::addMineraux(int nombre) {
    int * resultCoordonate;
    for (int i = 0; i < nombre; ++i) {
        resultCoordonate = generateCoordonate();

        Mineraux * mineraux = new Mineraux(resultCoordonate[0], resultCoordonate[1]);

        this->listeMouton[i].coordonates[0] = mineraux->coordonates[0];
        this->listeMouton[i].coordonates[1] = mineraux->coordonates[1];
    }
}

int * Game::generateCoordonate() {
    int xCoordonate = rand() % this->size[0];
    int yCoordonate = rand() % this->size[1];

    bool coordonates = searchInArray(xCoordonate, yCoordonate);
    while (!coordonates) {
        xCoordonate = rand() % this->size[0];
        yCoordonate = rand() % this->size[1];
        coordonates = searchInArray(xCoordonate, yCoordonate);
    }

    static int resultCoordonate[2];
    resultCoordonate[0] = xCoordonate;
    resultCoordonate[1] = yCoordonate;

    return resultCoordonate;
}

bool Game::searchInArray(int x, int y) {
    bool canPlaceMouton = true;
    bool canPlaceLoup = true;
    bool canPlaceMineraux = true;

    //Find mouton;
    for (int i = 0; i < this->number_mouton; ++i) {
        if (this->listeMouton[i].coordonates[0] == x && this->listeMouton[i].coordonates[1] == y) {
            canPlaceMouton = false;
            break;
        }
    }

    //Find loup;
    for (int i = 0; i < this->number_loup; ++i) {
        if (this->listeLoup[i].coordonates[0] == x && this->listeLoup[i].coordonates[1] == y) {
            canPlaceLoup = false;
            break;
        }
    }

    //Find mineraux;
    for (int i = 0; i < this->number_mineraux; ++i) {
        if (this->listeMineraux[i].coordonates[0] == x && this->listeMineraux[i].coordonates[1] == y) {
            canPlaceMineraux = false;
            break;
        }
    }

    if (canPlaceMouton && canPlaceLoup  && canPlaceMineraux) {
        return true;
    }

    return false;
}

