#include "Game.h"

int main()
{

    Game game;

    game.musicPlay();

    while (game.isRunning())
    {
        game.checkEndGame();
        game.update();
        game.render();

    }

    return 0;
}