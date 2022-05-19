//
// Created by Picolas on 29/04/2022.
//

#ifndef C_PLUS_PLUS_PROJET_ESIEE_2022_BLOCK_H

#include "../Constants/Constants.h"

#define C_PLUS_PLUS_PROJET_ESIEE_2022_BLOCK_H


class Block {
public:
    Block();

    Block(int x, int y);

    int coordonates[2]{};

    string type = CASE_VIDE;
};


#endif //C_PLUS_PLUS_PROJET_ESIEE_2022_BLOCK_H
