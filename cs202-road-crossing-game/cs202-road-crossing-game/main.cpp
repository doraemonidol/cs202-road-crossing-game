#include "main.h"

int main()
{
    srand(static_cast<unsigned>(time(0)));
    GAME game;
    game.run();

    return 0;
}