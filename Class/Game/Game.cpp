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
    this->startGame();
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
    // ON affiche le jeu initial :
    this->showGame();

    this->state = "started";
    this->gameLoop();
}

// Boucle du jeu
void Game::gameLoop() {
    while(this->state == "started") {
        // On ajoute un tour
        this->incrementTour();

        // On fait pousser l'herbe en chaque début de tour
        this->changerMinerauxEnHerbe();

        // On retire 1 de faim aux mouton et loup en début de tour
        this->removeFaimAndVie();

        //check si un mouton meurt de faim ou vieillesse
        this->checkDieMouton();

        //check si un loup meurt de faim ou vieillesse
        this->checkDieLoup();

        //Bouger mouton et loup
        this->bestMoveMouton();
        this->bestMoveLoup();

        // On check les reproductions
        this->endReproductionMouton();
        this->reproductionMouton();

        // On check les reproductions
        this->endReproductionLoup();
        this->reproductionLoup();

        // On affiche le nombre d'element en jeu
        this->showNumberLife();

        //On affiche le jeu
        this->showGame();

        // On affiche les Evenements
        this->showEvents();

        // on verifie si c'est la fin du jeu
        this->checkEndGame();

        /*
        cout << "Appuyez sur entrer pour continuer" << endl;
        cin.ignore();
         */
    }
}

void Game::addLoup(int nombre) {
    int * resultCoordonate;
    for (int i = 0; i < nombre; ++i) {
        resultCoordonate = generateCoordonate();

        Loup loup(resultCoordonate[0], resultCoordonate[1]);
        loup.setRandomSexe();
        this->listeLoup.push_back(loup);
    }
}

void Game::addMouton(int nombre) {
    int * resultCoordonate;
    for (int i = 0; i < nombre; ++i) {
        resultCoordonate = generateCoordonate();

        Mouton mouton(resultCoordonate[0], resultCoordonate[1]);
        mouton.setRandomSexe();
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
    //srand (time(NULL));

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

        this->listeMouton[getIndexMouton(mouton)].faim = 5;

        //find herbe;
        int indexHerbe = 0;
        for(Herbe _herbe: this->listeHerbe) {
            if (_herbe.coordonates[0] == herbe.coordonates[0] && _herbe.coordonates[1] == herbe.coordonates[1]) {
                break;
            }
            indexHerbe++;
        }

        this->listeHerbe.erase( this->listeHerbe.begin() + (indexHerbe));
    }
}

void Game::loupMangeMouton(Mouton& mouton, Loup &loup) {
    if (getBlockType(mouton.coordonates[0], mouton.coordonates[1]) == MOUTON) {
        Evenements event(MOUTON_MEURT_LOUP, mouton.coordonates[0], mouton.coordonates[1]);
        this->listeEvenements.push_back(event);

        this->listeLoup[getIndexLoup(loup)].faim = 10;

        this->listeMouton.erase( this->listeMouton.begin() + (getIndexMouton(mouton)));

        Mineraux mineraux(mouton.coordonates[0], mouton.coordonates[1]);
        this->listeMineraux.push_back(mineraux);
    }
}

void Game::changerMinerauxEnHerbe() {
    for (Mineraux mineraux : this->listeMineraux) {

        int oldX = mineraux.coordonates[0];
        int oldY = mineraux.coordonates[1];
        this->listeMineraux.erase( this->listeMineraux.begin() + (getIndexMineraux(mineraux)));

        Herbe herbe(oldX, oldY);
        this->listeHerbe.push_back(herbe);

        Evenements event(HERBE_POUSSE, herbe.coordonates[0], herbe.coordonates[1]);
        this->listeEvenements.push_back(event);
    }
}

void Game::killMouton(Mouton &mouton, string type) {
    if (type != "") {
        Evenements event(type, mouton.coordonates[0], mouton.coordonates[1]);
        this->listeEvenements.push_back(event);
    }

    Mineraux mineraux(mouton.coordonates[0], mouton.coordonates[1]);
    this->listeMineraux.push_back(mineraux);

    this->listeMouton.erase( this->listeMouton.begin() + (getIndexMouton(mouton)));
}

void Game::killLoup(Loup &loup, string type) {
    Evenements event(type, loup.coordonates[0], loup.coordonates[1]);
    this->listeEvenements.push_back(event);

    Mineraux mineraux(loup.coordonates[0], loup.coordonates[1]);
    this->listeMineraux.push_back(mineraux);

    this->listeLoup.erase( this->listeLoup.begin() + (getIndexLoup(loup)));
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
    // On clear les events
    listeEvenements.clear();
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
        if (mouton.faim <= 0) {
            this->killMouton(mouton, MOUTON_MEURT_FAIM);
            continue;
        }
        if (mouton.vie <= 0) {
            this->killMouton(mouton, MOUTON_MEURT_VIELLESSE);
            continue;
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

void Game::removeFaimAndVie() {
    for (Mouton mouton : this->listeMouton) {
        this->listeMouton[getIndexMouton(mouton)].faim -= 1;
        this->listeMouton[getIndexMouton(mouton)].vie -= 1;
    }

    for (Loup loup : this->listeLoup) {
        this->listeLoup[getIndexLoup(loup)].faim -= 1;
        this->listeLoup[getIndexLoup(loup)].vie -= 1;
    }
}

void Game::bestMoveMouton() {
    bool moutonMoved = false;
    for (Mouton mouton : this->listeMouton) {

        // Boucle herbe (< 5 pour éviter de gaspiller de l'herbe
        if (mouton.faim < 5) {
            for (int y = -1; y < 1; ++y) {
                for (int x = -1; x <= 1; ++x) {
                    if (getBlockType(numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]), numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1])) == HERBE) {
                        Herbe herbe = getHerbe(mouton.coordonates[0] + x, mouton.coordonates[1] + y);
                        this->moutonMangeHerbe(herbe, mouton);
                    }
                }
            }
        }

        moutonMoved = false;
        // On bouge
        for (int y = -1; y < 1; ++y) {
            if (moutonMoved)
                break;
            for (int x = -1; x <= 1; ++x) {
                if (moutonMoved)
                    break;

                if (getBlockType(numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]), numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1])) == CASE_VIDE) {
                    int oldX = mouton.coordonates[0];
                    int oldY = mouton.coordonates[1];

                    // On change ses coordonnées :
                    this->listeMouton[getIndexMouton(mouton)].coordonates[0] = numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]);
                    this->listeMouton[getIndexMouton(mouton)].coordonates[1] = numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1]);
                    moutonMoved = true;

                    // On affiche un message
                    //cout << "Le mouton s'est déplacé de [" << to_string(oldX + 1) + intToLetter(oldY) + "] à ";
                    //cout << "[" + to_string(this->listeMouton[getIndexMouton(mouton)].coordonates[0] + 1) + intToLetter(this->listeMouton[getIndexMouton(mouton)].coordonates[1]) + "] " << endl;
                }
            }
        }

    }
}

void Game::bestMoveLoup() {
    bool loupMoved = false;
    for (Loup loup : this->listeLoup) {

        // Boucle mouton < 10 pour éviter de tuer des moutons pour rien
        if (loup.faim < 10) {
            for (int y = -1; y < 1; ++y) {
                for (int x = -1; x <= 1; ++x) {
                    if (getBlockType(numberNotOutOfBound(loup.coordonates[0] + x, this->size[0]),
                                     numberNotOutOfBound(loup.coordonates[1] + y, this->size[1])) == MOUTON) {
                        Mouton mouton = getMouton(loup.coordonates[0] + x, loup.coordonates[1] + y);
                        this->loupMangeMouton(mouton, loup);
                    }
                }
            }
        }

        loupMoved = false;
        // On bouge
        for (int y = -1; y < 1; ++y) {
            if (loupMoved)
                break;
            for (int x = -1; x <= 1; ++x) {
                if (loupMoved)
                    break;

                if (getBlockType(numberNotOutOfBound(loup.coordonates[0] + x, this->size[0]), numberNotOutOfBound(loup.coordonates[1] + y, this->size[1])) == CASE_VIDE) {
                    int oldX = loup.coordonates[0];
                    int oldY = loup.coordonates[1];

                    /*
                    cout << "loup x = coordonates : " << loup.coordonates[0] + x << endl;
                    cout << "not ou bound : " << numberNotOutOfBound(loup.coordonates[0] + x, this->size[0]) << endl;
                    cout << "test x strong : " << this->listeLoup[getIndexLoup(loup)].coordonates[0] << endl;
                    cout << "test x not strng : " << this->listeLoup[getIndexLoup(loup)].coordonates[0] + 1 << endl;
                     */
                    // On change ses coordonnées :
                    this->listeLoup[getIndexLoup(loup)].coordonates[0] = numberNotOutOfBound(loup.coordonates[0] + x, this->size[0]);
                    this->listeLoup[getIndexLoup(loup)].coordonates[1] = numberNotOutOfBound(loup.coordonates[1] + y, this->size[1]);
                    loupMoved = true;

                    // On affiche un message
                    //cout << "Le loup s'est déplacé de [" << to_string(oldX + 1) + intToLetter(oldY) + "] à ";
                    //cout << "[" + to_string(this->listeLoup[getIndexLoup(loup)].coordonates[0]) + intToLetter(this->listeLoup[getIndexLoup(loup)].coordonates[1]) + "] " << endl;
                }
            }
        }

    }
}

int Game::numberNotSupOrMinOne(int number) {
    if (number >= 1)
        return 1;
    if (number <= -1)
        return -1;
    return 0;
}

int Game::numberNotOutOfBound(int number, int size) {
    if (number > size) {
        return size;
    }
    if (number < 0) {
        return 0;
    }
    return number;
}

Herbe Game::getHerbe(int x, int y) {
    //find herbe;
    int indexHerbe = 0;
    for(Herbe herbe: this->listeHerbe) {
        if (herbe.coordonates[0] == x && herbe.coordonates[1] == y) {
            break;
        }
        indexHerbe++;
    }

    return this->listeHerbe[indexHerbe];
}

int Game::getIndexMouton(Mouton& mouton) {
    //find mouton;
    int indexMouton = 0;
    for(Mouton _mouton: this->listeMouton) {
        if (_mouton.coordonates[0] == mouton.coordonates[0] && _mouton.coordonates[1] == mouton.coordonates[1]) {
            break;
        }
        indexMouton++;
    }

    return indexMouton;
}

int Game::getIndexLoup(Loup& loup) {
    //find loup;
    int indexLoup = 0;
    for(Loup _loup: this->listeLoup) {
        if (_loup.coordonates[0] == loup.coordonates[0] && _loup.coordonates[1] == loup.coordonates[1]) {
            break;
        }
        indexLoup++;
    }

    return indexLoup;
}

void Game::randomMoveMouton() {

    bool moutonMoved = false;
    // ON parcour la liste des moutons
    for(Mouton mouton : this->listeMouton) {
        moutonMoved = false;
        cout << "index = " << this->getIndexMouton(mouton) << endl;
        // On va chercher sur la ligne X :
        for (int y = -1; y <= 1; ++y) {
            // on check si le mouton à bougé:
            if (moutonMoved)
                break;
            cout << "Y = " << y << endl;

            for (int x = -1; x <= 1; ++x) {
                // on check si le mouton à bougé:
                if (moutonMoved)
                    break;

                cout << "X = " << x << endl;

                //cout << "[" + to_string(this->listeMouton[getIndexMouton(mouton)].coordonates[0] + x + 1) + intToLetter(this->listeMouton[getIndexMouton(mouton)].coordonates[1] + y) + "] " << endl;

                cout << "Block : ";

                cout << "[" + to_string(this->listeMouton[getIndexMouton(mouton)].coordonates[0] + x + 1) + intToLetter(this->listeMouton[getIndexMouton(mouton)].coordonates[1] + y) + "] ";
                cout << getBlockType(numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]), numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1])) << endl;

                // On check si c'est de l'herbe
                if (getBlockType(numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]), numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1])) == HERBE) {
                    Herbe herbe = getHerbe(mouton.coordonates[0] + x, mouton.coordonates[1] + y);
                    this->moutonMangeHerbe(herbe, mouton);
                } else if (getBlockType(numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]), numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1])) == CASE_VIDE) {
                    int oldX = mouton.coordonates[0];
                    int oldY = mouton.coordonates[1];

                    // On change ses coordonnées :
                    this->listeMouton[getIndexMouton(mouton)].coordonates[0] = numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]);
                    this->listeMouton[getIndexMouton(mouton)].coordonates[1] = numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1]);
                    moutonMoved = true;

                    // On affiche un message
                    cout << "Le mouton s'est déplacé de [" << to_string(oldX + 1) + intToLetter(oldY) + "] à ";
                    cout << "[" + to_string(this->listeMouton[getIndexMouton(mouton)].coordonates[0] + 1) + intToLetter(this->listeMouton[getIndexMouton(mouton)].coordonates[1]) + "] " << endl;
                }
            }
        }

    }



        /*
        bool moved = false;
        for (int y = -1; y <= 1; ++y) {
            if (moved) {
                break;
            }
            for (int x = -1; x <= 1; ++x) {
                if (moved) {
                    break;
                }
                if (getBlockType(numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]), numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1])) != LOUP &&
                        getBlockType(numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]), numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1])) != MOUTON
                        && getBlockType(numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]), numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1])) != MINERAUX) {

                    // Si c'est de l'herbe alors on mange
                    if (getBlockType(numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]), numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1])) == HERBE) {
                        //Manger herbe
                        Herbe herbe = getHerbe(mouton.coordonates[0] + x, mouton.coordonates[1] + y);
                        this->moutonMangeHerbe(herbe, mouton);
                    } else {
                        // on déplace le mouton
                        int oldX = mouton.coordonates[0];
                        int oldY = mouton.coordonates[1];
                        this->listeMouton[getIndexMouton(mouton)].coordonates[0] = numberNotSupOrMinOne(mouton.coordonates[0] + x);
                        this->listeMouton[getIndexMouton(mouton)].coordonates[1] = numberNotSupOrMinOne(mouton.coordonates[1] + y);
                        cout << "Le mouton s'est déplacé de [" << to_string(oldX + 1) + intToLetter(oldY) + "] à ";
                        cout << "[" + to_string(this->listeMouton[getIndexMouton(mouton)].coordonates[0] + 1) + intToLetter(this->listeMouton[getIndexMouton(mouton)].coordonates[1]) + "] " << endl;
                        moved = true;
                    }

                }
            }
        }
    }
    */
}

void Game::showNumberLife() {
    int numberLoup = this->listeLoup.size();
    int numberMouton = this->listeMouton.size();
    int numberHerbe = this->listeHerbe.size();
    int numberMineraux = this->listeMineraux.size();

    cout << "[INFO] Tour " << this->tour << " | Loup " << numberLoup << " | Mouton " << numberMouton << endl; // << " | Herbe " << numberHerbe << " | Mineraux " << numberMineraux
}

int Game::getIndexMineraux(Mineraux &mineraux) {
    //find mineraux;
    int indexMineraux = 0;
    for(Mineraux _mineraux: this->listeMineraux) {
        if (_mineraux.coordonates[0] == mineraux.coordonates[0] && _mineraux.coordonates[1] == mineraux.coordonates[1]) {
            break;
        }
        indexMineraux++;
    }

    return indexMineraux;
}

int Game::getIndexHerbe(Herbe &herbe) {
    //find herbe;
    int indexHerbe = 0;
    for(Herbe _herbe: this->listeHerbe) {
        if (_herbe.coordonates[0] == herbe.coordonates[0] && _herbe.coordonates[1] == herbe.coordonates[1]) {
            break;
        }
        indexHerbe++;
    }

    return indexHerbe;
}

void Game::checkEndGame() {
    if (this->listeMouton.empty() && this->listeLoup.empty() && this->listeMineraux.empty()) {
        this->state = "finished";
        cout << "Le jeu est terminé il ne reste plus que de l'herbe sur la map" << endl;
    }
}

void Game::reproductionMouton() {

    for (Mouton mouton: this->listeMouton) {

        for (int y = -1; y <= 1; ++y) {

            for (int x = -1; x <= 1; ++x) {

                if (getBlockType(numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]), numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1])) == MOUTON) {

                    Mouton firstMouton = this->listeMouton[getIndexMouton(mouton)];
                    Mouton reproductedMouton = getMouton(numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]),
                                                         numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1]));
                    Mouton secondMouton = this->listeMouton[getIndexMouton(reproductedMouton)];

                    // On verifie si il y a un male et une femelle:
                    if (canReproductedMouton(firstMouton, secondMouton)) {

                        if (this->listeMouton[getIndexMouton(mouton)].canReproducted &&
                            this->listeMouton[getIndexMouton(reproductedMouton)].canReproducted) {
                            // on bloque les moutons pour 1 tour
                            this->listeMouton[getIndexMouton(mouton)].canReproducted = false;
                            this->listeMouton[getIndexMouton(reproductedMouton)].canReproducted = false;

                            Evenements event(MOUTON_REPRODUCTION, mouton.coordonates[0], mouton.coordonates[1]);
                            this->listeEvenements.push_back(event);
                        } else {
                            continue;
                        }
                    } else {
                        continue;
                    }
                }
            }
        }
    }
}

Mouton Game::getMouton(int x, int y) {
    //find mouton;
    int indexMouton = 0;
    for(Mouton mouton: this->listeMouton) {
        if (mouton.coordonates[0] == x && mouton.coordonates[1] == y) {
            break;
        }
        indexMouton++;
    }

    return this->listeMouton[indexMouton];
}

Loup Game::getLoup(int x, int y) {
    //find loup;
    int indexLoup = 0;
    for(Loup loup: this->listeLoup) {
        if (loup.coordonates[0] == x && loup.coordonates[1] == y) {
            break;
        }
        indexLoup++;
    }

    return this->listeLoup[indexLoup];
}

bool Game::canReproductedMouton(Mouton& firstMouton, Mouton& secondMouton) {
    if (firstMouton.sexe != secondMouton.sexe)
        return true;
    return false;
}

bool Game::canReproductedLoup(Loup& firstLoup, Loup& secondLoup) {
    if (firstLoup.sexe != secondLoup.sexe)
        return true;
    return false;
}

void Game::endReproductionMouton() {
    bool reproducted = false;
    for (Mouton mouton : this->listeMouton) {
        reproducted = false;
        if (!mouton.canReproducted) {
            if (mouton.sexe == FEMININ) {
                for (int y = -1; y <= 1; ++y) {
                    if (reproducted)
                        break;
                    for (int x = -1; x <= 1; ++x) {
                        if (reproducted)
                            break;
                        if (getBlockType(numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]), numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1])) == MOUTON) {
                            Mouton mouton_reproducted = getMouton(numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]), numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1]));
                            if (!this->listeMouton[getIndexMouton(mouton_reproducted)].canReproducted) {
                                this->listeMouton[getIndexMouton(mouton_reproducted)].canReproducted = true;
                            }
                        }

                        if (getBlockType(numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]), numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1])) == CASE_VIDE) {

                            //On pose un nouveau bébé loup
                            Mouton babyMouton(numberNotOutOfBound(mouton.coordonates[0] + x, this->size[0]), numberNotOutOfBound(mouton.coordonates[1] + y, this->size[1]));
                            babyMouton.setRandomSexe();
                            this->listeMouton.push_back(babyMouton);

                            Evenements event(MOUTON_NAIT, babyMouton.coordonates[0], babyMouton.coordonates[1]);
                            this->listeEvenements.push_back(event);
                            reproducted = true;
                        }
                    }
                }
            }
            this->listeMouton[getIndexMouton(mouton)].canReproducted = true;
        }
    }
}

void Game::reproductionLoup() {
    for (Loup loup: this->listeLoup) {

        for (int y = -1; y <= 1; ++y) {

            for (int x = -1; x <= 1; ++x) {

                if (getBlockType(numberNotOutOfBound(loup.coordonates[0] + x, this->size[0]), numberNotOutOfBound(loup.coordonates[1] + y, this->size[1])) == LOUP) {

                    Loup firstLoup = this->listeLoup[getIndexLoup(loup)];
                    Loup reproductedLoup = getLoup(numberNotOutOfBound(loup.coordonates[0] + x, this->size[0]),
                                                   numberNotOutOfBound(loup.coordonates[1] + y, this->size[1]));
                    Loup secondLoup = this->listeLoup[getIndexLoup(reproductedLoup)];

                    // On verifie si il y a un male et une femelle:
                    if (canReproductedLoup(firstLoup, secondLoup)) {

                        if (this->listeLoup[getIndexLoup(loup)].canReproducted &&
                            this->listeLoup[getIndexLoup(reproductedLoup)].canReproducted) {
                            // on bloque les moutons pour 1 tour
                            this->listeLoup[getIndexLoup(loup)].canReproducted = false;
                            this->listeLoup[getIndexLoup(reproductedLoup)].canReproducted = false;

                            Evenements event(LOUP_REPRODUCTION, loup.coordonates[0], loup.coordonates[1]);
                            this->listeEvenements.push_back(event);
                        } else {
                            continue;
                        }
                    } else {
                        continue;
                    }
                }
            }
        }
    }
}

void Game::endReproductionLoup() {
    bool reproducted = false;
    for (Loup loup : this->listeLoup) {
        reproducted = false;
        if (!loup.canReproducted) {
            if (loup.sexe == FEMININ) {
                for (int y = -1; y <= 1; ++y) {
                    if (reproducted)
                        break;
                    for (int x = -1; x <= 1; ++x) {
                        if (reproducted)
                            break;
                        if (getBlockType(numberNotOutOfBound(loup.coordonates[0] + x, this->size[0]), numberNotOutOfBound(loup.coordonates[1] + y, this->size[1])) == LOUP) {
                            Loup loup_reproducted = getLoup(numberNotOutOfBound(loup.coordonates[0] + x, this->size[0]), numberNotOutOfBound(loup.coordonates[1] + y, this->size[1]));
                            if (!this->listeLoup[getIndexLoup(loup_reproducted)].canReproducted) {
                                this->listeLoup[getIndexLoup(loup_reproducted)].canReproducted = true;
                            }
                        }

                        if (getBlockType(numberNotOutOfBound(loup.coordonates[0] + x, this->size[0]), numberNotOutOfBound(loup.coordonates[1] + y, this->size[1])) == CASE_VIDE) {

                            //On pose un nouveau bébé loup
                            Loup babyLoup(numberNotOutOfBound(loup.coordonates[0] + x, this->size[0]), numberNotOutOfBound(loup.coordonates[1] + y, this->size[1]));
                            babyLoup.setRandomSexe();
                            this->listeLoup.push_back(babyLoup);

                            Evenements event(LOUP_NAIT, babyLoup.coordonates[0], babyLoup.coordonates[1]);
                            this->listeEvenements.push_back(event);
                            reproducted = true;
                        }
                    }
                }
            }
            this->listeLoup[getIndexLoup(loup)].canReproducted = true;
        }
    }
}

void Game::incrementTour() {
    this->tour++;
}


