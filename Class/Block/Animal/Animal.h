//
// Created by Nicolas PIPLARD on 23/04/2022.
//

#ifndef C_PLUS_PLUS_PROJET_ESIEE_2022_ANIMAL_H
#include "../Block.h"
#define C_PLUS_PLUS_PROJET_ESIEE_2022_ANIMAL_H


class Animal: public Block {
    int faim = 0;
    int vie = 0;

public:
    Animal(int x, int y);

    Animal();
};


#endif //C_PLUS_PLUS_PROJET_ESIEE_2022_ANIMAL_H
