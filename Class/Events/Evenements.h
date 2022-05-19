//
// Created by Nicolas PIPLARD on 19/05/2022.
//

#ifndef C_PLUS_PLUS_PROJET_ESIEE_2022_EVENEMENTS_H
#include <string>

using namespace std;
#define C_PLUS_PLUS_PROJET_ESIEE_2022_EVENEMENTS_H

class Evenements {
public:
    string type;
    int coordonates[2] {};

    Evenements(string type, int x, int y);
};


#endif //C_PLUS_PLUS_PROJET_ESIEE_2022_EVENEMENTS_H
