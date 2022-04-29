//
// Created by Nicolas PIPLARD on 29/04/2022.
//

#ifndef C_PLUS_PLUS_PROJET_ESIEE_2022_PLACE_H
#include "../Game/Game.h"
#include "../Constants/Constants.h"
#include <string>

using namespace std;
#define C_PLUS_PLUS_PROJET_ESIEE_2022_PLACE_H

class Place {

    static bool staticSearchInArray(int x, int y, Game game);

    static string getBlockType(int x, int y, Game game);

};


#endif //C_PLUS_PLUS_PROJET_ESIEE_2022_PLACE_H
