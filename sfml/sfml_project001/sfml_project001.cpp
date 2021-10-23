// sfml_project001.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include  "Game.h"


int main()
{
    //Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    //Init GAME Engine
    Game game;

    //loop--
    while (game.running() && !game.getEndGame()) {


        // update
        game.update();

        //render -
        game.render();

    }


    _getch();
    return 0;
}