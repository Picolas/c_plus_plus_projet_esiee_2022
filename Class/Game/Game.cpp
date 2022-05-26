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
    this->startGame();
}

Game::Game(int x, int y) {
    this->setSize(x, y);
    this->addLoup(number_loup);
    this->addMouton(number_mouton);
    this->addHerbe(number_herbe);
    this->addMineraux(number_mineraux);
    this->setShowGameDimansions();
    //this->startGame();
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
    this->gameLoop();
}


void Game::gameLoop() {
    while(this->state == "started") {

        // On retire 1 de faim aux mouton et loup en début de tour
        this->removeFaim();

        //check si un mouton meurt de faim ou vieillesse
        this->checkDieMouton();

        //check si un loup meurt de faim ou vieillesse
        this->checkDieLoup();

        //Bouger mouton
        //this->bestMoveMouton();


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

void Game::moutonMangeHerbe(Herbe& herbe, Mouton &mouton) {
    if (getBlockType(herbe.coordonates[0], herbe.coordonates[1]) == HERBE) {
        Evenements event(MOUTON_MANGE_HERBE, herbe.coordonates[0], herbe.coordonates[1]);
        this->listeEvenements.push_back(event);

        mouton.faim = 5;

        //find herbe;
        int indexHerbe = 0;
        for(Herbe _herbe: this->listeHerbe) {
            if (_herbe.coordonates[0] == herbe.coordonates[0] && _herbe.coordonates[1] == herbe.coordonates[1]) {
                break;
            }
            indexHerbe++;
        }

        this->listeHerbe.erase( this->listeHerbe.begin() + indexHerbe);
    }
}

void Game::loupMangeMouton(Mouton& mouton, Loup &loup) {
    if (getBlockType(mouton.coordonates[0], mouton.coordonates[1]) == MOUTON) {
        Evenements event(MOUTON_MEURT_LOUP, mouton.coordonates[0], mouton.coordonates[1]);
        this->listeEvenements.push_back(event);

        loup.faim = 10;

        //find mouton;
        int indexMouton = 0;
        for(Mouton _mouton: this->listeMouton) {
            if (_mouton.coordonates[0] == mouton.coordonates[0] && _mouton.coordonates[1] == mouton.coordonates[1]) {
                break;
            }
            indexMouton++;
        }

        this->listeMouton.erase( this->listeMouton.begin() + indexMouton);

        Mineraux mineraux(mouton.coordonates[0], mouton.coordonates[1]);
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

    Evenements event(HERBE_POUSSE, herbe.coordonates[0], herbe.coordonates[1]);
    this->listeEvenements.push_back(event);
}

void Game::killMouton(Mouton &mouton, string type) {
    Evenements event(type, mouton.coordonates[0], mouton.coordonates[1]);
    this->listeEvenements.push_back(event);

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

void Game::killLoup(Loup &loup, string type) {
    Evenements event(type, loup.coordonates[0], loup.coordonates[1]);
    this->listeEvenements.push_back(event);

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
    int taille = 10;
    int spaceToDel = 1;
    if (this->size[0] > 10){
        for (int i = 0; i < this->size[0]; i++){
            if( i > taille) {
            spaceToDel += 1;
            taille *= 10;
            }
        }
    }
    for (int i = 0; i < this->size[0]; i++) {
        line += " "; // espace de la colonne arrière cdt le | séparant chaque colonne
        for (int j = 0; j < this->tiret_space; j++){
            if(j == (this->tiret_space / 2) + 1){
                line += to_string(i + 1);
            }
            else {
                line += " ";
            }
        }
        if (i > 8){
            for (int k = 1; k < spaceToDel; k++){
                line = line.substr (0, line.length()-1);
            }
        }
    }
    return line;
}

void Game::setShowGameDimansions() {
    int taille = 10;
    while(taille < this->size[0]){
        this->tiret_space += 2;
        taille *= 10;
    }
}

void Game::showGame() {
    //calcul de l'espacement entre chaque zone en fonction de la taille de la fenetre du jeu
    int separator_space = 2;

    // calcul du blanc � mettre si aucune objet dans la case
    string blanc = "";
    for (int j = 0; j < this->tiret_space; j++){
        blanc += " ";
    }
    // calcul du nbr d'espace � mettre de chaque cote de la lettre de l'objet
    string blockspace = "";
    for (int j = 0; j < this->tiret_space / 2; j++){
        blockspace += " ";
    }
    cout << this->firstLine() << endl; // affichage de la premi�re ligne contenant les chiffres
    cout << this->secondLine() << endl; // d�marrage de l'affichage du jeu
    string separator = ""; // espace s�parant la grille du bord de l'�cran
    for (int i = 0; i < separator_space; i++){
        separator += " ";
    }
    for (int y = 0; y < this->size[1]; y++) {
        if ( y > 25 ) separator = " ";
        int letter = y;
        if (y > 25){
            int second_letter = 0;
            for(int i = 0; i <= y / 26; i++){
                second_letter = i;
            }
            letter -= (26 * second_letter);
            cout << intToLetter(second_letter - 1); // -1 car traité a partir de 0 et non 1 dans la fonction
        }
        cout << intToLetter(letter); // Affichage de la lettre correspondant à la ligne
        for (int x = 0; x < size[0]; x++) {
            separator += "|" ;//+ blanc;
            string block = getBlockType(x, y);
            if (block != CASE_VIDE){
                if(block == MOUTON) {
                    separator += blockspace + "M" + blockspace;
                } else if (block == LOUP) {
                    separator += blockspace + "L" + blockspace;
                } else if (block == HERBE) {
                    separator += blockspace + "H" + blockspace;
                } else if (block == MINERAUX) {
                    separator += blockspace + "S" + blockspace;
                }
            }
            else{
                separator += blanc;
            }
        }
        cout << separator; // �criture de la ligne trait�
        cout << "|" << endl; // ajout de s�parateur de fin
        separator = "  "; // remise � z�ro du s�parateur pour la nouvelle ligne
        cout << this->secondLine() << endl; // affichage de la ligne du dessous ( aussi le contour bas )
    }
}

string Game::secondLine() {
     // d�marrer avec une s�paration de 3 ( colle au reste de l'affichage )
    string line = "   ";
    string tiret = "";
    for (int j = 0; j < this->tiret_space; j++){
        tiret += "-";
    }
    for (int i = 0; i < this->size[0]; ++i) {
        if (i == 0) {
            line += "+" + tiret;
        } else if (i >= this->size[0] - 1) {
            line += "+" + tiret + "+";
        } else {
            line += "+" + tiret;
        }
    }
    return line;
}

string Game::letterLine() {
    string line = " ";

}

char Game::intToLetter(int value) {
    return (char)(value + 1 + 64);
}

void Game::showEvents() {
    for (Evenements event: listeEvenements) {
        string result = "[" + to_string(event.coordonates[0] + 1) + intToLetter(event.coordonates[1]) + "] " + event.type;
        cout << result << endl;
    }
    /*
     * BUG EN ATTENTE POUR STACKER
    int indexCurrentEvent = 0;
    for (Evenements event: listeEvenements) {
        string result = "[" + to_string(event.coordonates[0]) + intToLetter(event.coordonates[1]);
        string eventType = event.type;
        int indexEvent = 0;

        for (int i = 0; i < listeEvenements.size(); i++) {
            if(event.type == listeEvenements[i].type && (event.coordonates[0] != listeEvenements[i].coordonates[0] || event.coordonates[1] != listeEvenements[i].coordonates[1])) {
                result += ", " + to_string(listeEvenements[i].coordonates[0]) + intToLetter(listeEvenements[i].coordonates[1]);
                this->listeEvenements.erase( this->listeEvenements.begin() + indexEvent);
            }
            indexEvent++;
        }
        result += "] " + eventType;
        cout << result << endl;
    }
    */
}

void Game::checkDieMouton() {
    for (Mouton mouton : this->listeMouton) {
        if (mouton.faim == 0) {
            this->killMouton(mouton, MOUTON_MEURT_FAIM);
        }
        if (mouton.vie == 0) {
            this->killMouton(mouton, MOUTON_MEURT_VIELLESSE);
        }
    }
}

void Game::checkDieLoup() {
    for (Loup loup : this->listeLoup) {
        if (loup.faim <= 0) {
            this->killLoup(loup, LOUP_MEURT_FAIM);
        }
        if (loup.vie <= 0) {
            this->killLoup(loup, LOUP_MEURT_VIELLESSE);
        }
    }
}

void Game::removeFaim() {
    for (Mouton mouton : this->listeMouton) {
        mouton.faim -= 1;
    }

    for (Loup loup : this->listeLoup) {
        loup.faim -= 1;
    }
}

void Game::bestMoveMouton() {
    for(Mouton mouton : this->listeMouton) {
        bool findHerbe = false;
        for (int i = -2; i < 2; ++i) {
            for (int j = -2; j < 2; ++j) {
                if (getBlockType(mouton.coordonates[0] + i, mouton.coordonates[1] + i) == HERBE) {
                    findHerbe = true;
                    if (getBlockType(numberNotSupOrMinOne(i), numberNotSupOrMinOne(j)) == CASE_VIDE || getBlockType(numberNotSupOrMinOne(i), numberNotSupOrMinOne(j)) == HERBE || getBlockType(numberNotSupOrMinOne(i), numberNotSupOrMinOne(j)) == MINERAUX) {
                        mouton.coordonates[0] = numberNotSupOrMinOne(i);
                        mouton.coordonates[1] = numberNotSupOrMinOne(j);
                    } else {
                        findHerbe = false;
                    }
                }
            }
        }
        if (!findHerbe) {
            for (int i = -2; i < 2; ++i) {
                for (int j = -2; j < 2; ++j) {
                    if (getBlockType(numberNotSupOrMinOne(i), numberNotSupOrMinOne(j)) == CASE_VIDE || getBlockType(numberNotSupOrMinOne(i), numberNotSupOrMinOne(j)) == HERBE || getBlockType(numberNotSupOrMinOne(i), numberNotSupOrMinOne(j)) == MINERAUX) {
                        mouton.coordonates[0] = numberNotSupOrMinOne(i);
                        mouton.coordonates[1] = numberNotSupOrMinOne(j);
                    }
                }
            }
        }
        cout << "le mouton a bougé";
    }
}

int Game::numberNotSupOrMinOne(int number) {
    if (number >= 1)
        return 1;
    if (number <= -1)
        return -1;
    return 0;
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



