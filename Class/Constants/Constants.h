//
// Created by Nicolas PIPLARD on 29/04/2022.
//

#ifndef C_PLUS_PLUS_PROJET_ESIEE_2022_CONSTANTS_H
#include <string>

using namespace std;
#define C_PLUS_PLUS_PROJET_ESIEE_2022_CONSTANTS_H

const string MOUTON = "Mouton";
const string LOUP = "Loup";
const string HERBE = "Herbe";
const string MINERAUX = "Mineraux";
const string CASE_VIDE = "Case Vide";
const string ANIMAL = "Animal";

// Evenements
const string LOUP_MEURT_FAIM = "Un loup meurt de faim.";
const string LOUP_MEURT_VIELLESSE = "Un loup meurt de vieillesse.";
const string MOUTON_MEURT_FAIM = "Un mouton meurt de faim.";
const string MOUTON_MEURT_LOUP = "Un mouton à servi de repas à un loup.";
const string MOUTON_MEURT_VIELLESSE = "Un mouton meurt de vieillesse";
const string MOUTON_MANGE_HERBE = "De l'herbe a été mangé par un mouton";
const string HERBE_POUSSE = "De l'herbe repousse !";

// Tirets
const int TIRETS = 5;

#endif //C_PLUS_PLUS_PROJET_ESIEE_2022_CONSTANTS_H
