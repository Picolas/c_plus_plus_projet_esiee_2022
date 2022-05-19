//
// Created by Nicolas PIPLARD on 19/05/2022.
//

#include "Evenements.h"

Evenements::Evenements(string type, int x, int y) {
    this->type = type;
    this->coordonates[0] = x;
    this->coordonates[1] = y;
}