//
// Created by Nicolas PIPLARD on 24/04/2022.
//

#include "Game.h"

Game::Game(int number_loup, int number_mouton, int number_mineraux, int x, int y): number_loup(number_loup), number_mouton(number_mouton), number_mineraux(number_mineraux){
    this->setSize(x, y);
    this->fillMapBlock();
    this->addLoup(number_loup);
    this->addMouton(number_mouton);
    this->addHerbe(number_herbe);
    this->addMineraux(number_mineraux);
}

Game::Game(int x, int y) {
    this->setSize(x, y);
    this->fillMapBlock();
    this->addLoup(number_loup);
    this->addMouton(number_mouton);
    this->addHerbe(number_herbe);
    this->addMineraux(number_mineraux);
}

Game::Game(int numberLoup, int numberMouton, int numberMineraux, int numberHerbe, int x, int y) : number_loup(numberLoup),
                                                                                    number_mouton(numberMouton),
                                                                                    number_mineraux(numberMineraux),
                                                                                    number_herbe(numberHerbe) {
    this->setSize(x, y);
    this->fillMapBlock();
}

Game::Game() {
    this->startGame();
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

        Loup loup(resultCoordonate[0], resultCoordonate[1]);
        //this->listeLoup.push_back(loup);
        this->listeBlock[resultCoordonate[0]][resultCoordonate[1]] = loup;
    }
}

void Game::addMouton(int nombre) {
    int * resultCoordonate;
    for (int i = 0; i < nombre; ++i) {
        resultCoordonate = generateCoordonate();

        Mouton mouton(resultCoordonate[0], resultCoordonate[1]);
        //this->listeMouton.push_back(mouton);
        this->listeBlock[resultCoordonate[0]][resultCoordonate[1]] = mouton;
    }
}

void Game::addMineraux(int nombre) {
    int * resultCoordonate;
    for (int i = 0; i < nombre; ++i) {
        resultCoordonate = generateCoordonate();

        Mineraux mineraux(resultCoordonate[0], resultCoordonate[1]);
        //this->listeMineraux.push_back(mineraux);
        this->listeBlock[resultCoordonate[0]][resultCoordonate[1]] = mineraux;
    }
}

void Game::addHerbe(int nombre) {
    int * resultCoordonate;
    for (int i = 0; i < nombre; ++i) {
        resultCoordonate = generateCoordonate();

        Herbe herbe(resultCoordonate[0], resultCoordonate[1]);
        //this->listeHerbe.push_back(herbe);
        this->listeBlock[resultCoordonate[0]][resultCoordonate[1]] = herbe;
    }
}

int * Game::generateCoordonate() {
    srand (time(NULL));

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
    if (this->listeBlock[x][y].type == CASE_VIDE) {
        return true;
    }
    return false;

    bool canPlaceMouton = true;
    bool canPlaceLoup = true;
    bool canPlaceMineraux = true;
    bool canPlaceHerbe = true;

    //Find mouton;
    for (Mouton &mouton : this->listeMouton) {
        if (mouton.coordonates[0] == x && mouton.coordonates[1] == y) {
            canPlaceMouton = false;
            break;
        }
    }

    //Find loup;
    for (Loup &loup : this->listeLoup) {
        if (loup.coordonates[0] == x && loup.coordonates[1] == y) {
            canPlaceLoup = false;
            break;
        }
    }

    //Find mineraux;
    for (Mineraux &mineraux : this->listeMineraux) {
        if (mineraux.coordonates[0] == x && mineraux.coordonates[1] == y) {
            canPlaceMineraux = false;
            break;
        }
    }

    //Find herbe;
    for (Herbe &herbe : this->listeHerbe) {
        if (herbe.coordonates[0] == x && herbe.coordonates[1] == y) {
            canPlaceHerbe = false;
            break;
        }
    }

    if (canPlaceMouton && canPlaceLoup  && canPlaceMineraux && canPlaceHerbe) {
        return true;
    }

    return false;
}

string Game::getBlockType(int x, int y) {
    return this->listeBlock[x][y].type;

    //Find mouton;
    for (Mouton &mouton : this->listeMouton) {
        if (mouton.coordonates[0] == x && mouton.coordonates[1] == y) {
            return MOUTON;
        }
    }

    //Find loup;
    for (Loup &loup : this->listeLoup) {
        if (loup.coordonates[0] == x && loup.coordonates[1] == y) {
            return LOUP;
        }
    }

    //Find mineraux;
    for (Mineraux &mineraux : this->listeMineraux) {
        if (mineraux.coordonates[0] == x && mineraux.coordonates[1] == y) {
            return MINERAUX;
        }
    }

    //Find herbe;
    for (Herbe &herbe : this->listeHerbe) {
        if (herbe.coordonates[0] == x && herbe.coordonates[1] == y) {
            return HERBE;
        }
    }

    return CASE_VIDE;
}

void Game::moutonMangeHerbe(int x, int y, Mouton &mouton) {
    if (getBlockType(x, y) == HERBE) {
        mouton.faim = 5;

        this->listeBlock[x][y] = Block(x, y);
    }
}

void Game::loupMangeMouton(int x, int y, Loup &loup) {
    if (getBlockType(x, y) == MOUTON) {
        loup.faim = 10;

        this->listeBlock[x][y] = Mineraux(x, y);
    }
}

void Game::initMap() {
    this->listeBlock.resize(this->size[0]);
    for ( int i = 0 ; i < this->size[1] ; i++ )
        this->listeBlock[i].resize(this->size[1]);

    for (int i = 0; i < this->size[0]; ++i) {
        for (int j = 0; j < size[1]; ++j) {
            this->listeBlock[i][j] = Block(i, j);
        }
    }

    for (Mineraux &mineraux : this->listeMineraux) {
        this->listeBlock[mineraux.coordonates[0]][mineraux.coordonates[1]] = mineraux;
    }

    for (Loup &loup : this->listeLoup) {
        this->listeBlock[loup.coordonates[0]][loup.coordonates[1]] = loup;
    }

    for (Herbe &herbe : this->listeHerbe) {
        this->listeBlock[herbe.coordonates[0]][herbe.coordonates[1]] = herbe;
    }

    for (Mouton &mouton : this->listeMouton) {
        this->listeBlock[mouton.coordonates[0]][mouton.coordonates[1]] = mouton;
    }
}

void Game::fillMapBlock() {
    for (int i = 0; i < this->size[0]; ++i) {
        for (int j = 0; j < this->size[1]; ++j) {
            this->listeBlock[i][j] = Block(i, j);
        }
    }
}



