//
// Created by Nicolas PIPLARD on 23/04/2022.
//

#include "Animal.h"

Animal::Animal(int x, int y) : Block(x, y) {
}

void Animal::setRandomSexe() {
    srand (time(NULL));

    int random = rand() % 1;

    if (random == 0) {
        this->sexe = MASCULIN;
    } else {
        this->sexe = FEMININ;
    }
}

Animal::Animal() = default;
