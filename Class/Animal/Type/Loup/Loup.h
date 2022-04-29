//
// Created by Nicolas PIPLARD on 23/04/2022.
//

#ifndef C_PLUS_PLUS_PROJET_ESIEE_2022_LOUP_H
#include "../../Animal.h"
#define C_PLUS_PLUS_PROJET_ESIEE_2022_LOUP_H


class Loup: public Animal {

public:
    int faim = 10;
    int vie = 60;

    Loup(int x, int y);

    Loup();
};


#endif //C_PLUS_PLUS_PROJET_ESIEE_2022_LOUP_H
