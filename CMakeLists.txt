cmake_minimum_required(VERSION 3.17)
project(c_plus_plus_projet_esiee_2022)

set(CMAKE_CXX_STANDARD 14)


add_executable(c_plus_plus_projet_esiee_2022 main.cpp
        Class/Helpers/Place.cpp Class/Helpers/Place.h
        Class/Game/Game.cpp Class/Game/Game.h
        Class/Block/Animal/Animal.cpp Class/Block/Animal/Animal.h
        Class/Block/Animal/Type/Loup/Loup.cpp Class/Block/Animal/Type/Loup/Loup.h
        Class/Block/Animal/Type/Mouton/Mouton.cpp Class/Block/Animal/Type/Mouton/Mouton.h
        Class/Constants/Constants.h
        Class/Block/World/Herbe.cpp Class/Block/World/Herbe.h
        Class/Block/World/Mineraux.cpp Class/Block/World/Mineraux.h
        Class/Block/Block.cpp Class/Block/Block.h)
