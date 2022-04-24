//
// Created by Nicolas PIPLARD on 23/04/2022.
//

#ifndef C_PLUS_PLUS_PROJET_ESIEE_2022_MOUTON_H
#include "../../Animal.h"
#define C_PLUS_PLUS_PROJET_ESIEE_2022_MOUTON_H


class Mouton: public Animal {

public:
    int faim = 5;
    int vie = 50;

    Mouton(int x, int y);
};


#endif //C_PLUS_PLUS_PROJET_ESIEE_2022_MOUTON_H