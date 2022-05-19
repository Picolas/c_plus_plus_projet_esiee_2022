//
// Created by Nicolas PIPLARD on 24/04/2022.
//

#include "Game.h"

Game::Game(int number_loup, int number_mouton, int number_mineraux, int x, int y): number_loup(number_loup), number_mouton(number_mouton), number_mineraux(number_mineraux){
    this->setSize(x, y);
    this->addLoup(number_loup);
    this->addMouton(number_mouton);
    this->addHerbe(number_herbe);
    this->addMineraux(number_mineraux);
}

Game::Game(int x, int y) {
    this->setSize(x, y);
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
        this->listeLoup.push_back(loup);
    }
}

void Game::addMouton(int nombre) {
    int * resultCoordonate;
    for (int i = 0; i < nombre; ++i) {
        resultCoordonate = generateCoordonate();

        Mouton mouton(resultCoordonate[0], resultCoordonate[1]);
        this->listeMouton.push_back(mouton);
    }
}

void Game::addMineraux(int nombre) {
    int * resultCoordonate;
    for (int i = 0; i < nombre; ++i) {
        resultCoordonate = generateCoordonate();

        Mineraux mineraux(resultCoordonate[0], resultCoordonate[1]);
        this->listeMineraux.push_back(mineraux);
    }
}

void Game::addHerbe(int nombre) {
    int * resultCoordonate;
    for (int i = 0; i < nombre; ++i) {
        resultCoordonate = generateCoordonate();

        Herbe herbe(resultCoordonate[0], resultCoordonate[1]);
        this->listeHerbe.push_back(herbe);
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

        //find herbe;
        int indexHerbe = 0;
        for(Herbe herbe: this->listeHerbe) {
            if (herbe.coordonates[0] == x && herbe.coordonates[1] == y) {
                break;
            }
            indexHerbe++;
        }

        this->listeHerbe.erase( this->listeHerbe.begin() + indexHerbe);
    }
}

void Game::loupMangeMouton(int x, int y, Loup &loup) {
    if (getBlockType(x, y) == MOUTON) {
        loup.faim = 10;

        //find mouton;
        int indexMouton = 0;
        for(Mouton mouton: this->listeMouton) {
            if (mouton.coordonates[0] == x && mouton.coordonates[1] == y) {
                break;
            }
            indexMouton++;
        }

        this->listeMouton.erase( this->listeMouton.begin() + indexMouton);

        Mineraux mineraux(x, y);
        this->listeMineraux.push_back(mineraux);
    }
}

void Game::changerMinerauxEnHerbe(Mineraux &mineraux) {
    int x, y;
    x = mineraux.coordonates[0];
    y = mineraux.coordonates[1];

    //find mineraux;
    int indexMineraux = 0;
    for(Mineraux mineraux: this->listeMineraux) {
        if (mineraux.coordonates[0] == x && mineraux.coordonates[1] == y) {
            break;
        }
        indexMineraux++;
    }

    this->listeMineraux.erase( this->listeMineraux.begin() + indexMineraux);

    Herbe herbe(x, y);
    this->listeHerbe.push_back(herbe);
}

void Game::killMouton(Mouton &mouton) {
    //find mouton;
    int indexMouton = 0;
    for(Mouton _mouton: this->listeMouton) {
        if (_mouton.coordonates[0] == mouton.coordonates[0] && _mouton.coordonates[1] == mouton.coordonates[1]) {
            break;
        }
        indexMouton++;
    }

    this->listeMouton.erase( this->listeMouton.begin() + indexMouton);
}

void Game::killLoup(Loup &loup) {
    //find loup;
    int indexLoup = 0;
    for(Loup _loup: this->listeLoup) {
        if (_loup.coordonates[0] == loup.coordonates[0] && _loup.coordonates[1] == loup.coordonates[1]) {
            break;
        }
        indexLoup++;
    }

    this->listeLoup.erase( this->listeLoup.begin() + indexLoup);
}

string Game::firstLine() {
    // first line
    string line = "  ";
    for (int i = 0; i < this->size[0]; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (j == 5) {
                line += to_string(i + 1);
            } else {
                line += " ";
            }
        }
    }
    return line;
}

void Game::showGame() {
    cout << this->firstLine() << endl;
    cout << this->secondLine() << endl;
    for (int i = 0; i < this->size[0]; ++i) {
        for (int j = 0; j < size[1]; ++j) {

        }
    }
    cout << this->secondLine() << endl;
}

string Game::secondLine() {
    string line = "   ";
    for (int i = 0; i < this->size[0]; ++i) {
        if (i == 0) {
            line += "+-------";
        } else if (i >= this->size[0] - 1) {
            line += "+-------+";
        } else {
            line += "+-------";
        }
    }
    return line;
}

string Game::letterLine() {
    string line = " ";

}


/*
void Game::initMap() {
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
*/

/*
void Game::fillMapBlock() {
    this->rezizeListBlock();
    for (int i = 0; i < this->size[0]; ++i) {
        for (int j = 0; j < this->size[1]; ++j) {
            this->listeBlock[i][j] = block;
        }
    }
}
 */

/*
void Game::rezizeListBlock() {
    this->listeBlock.resize(this->size[0], vector<Block*>(this->size[0]));
}
*/



