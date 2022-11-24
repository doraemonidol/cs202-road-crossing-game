#include "OBSTACLE.h"
#include "UFO.h"
#include "METEOR.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "main.h"
#include "SPACESHIP.h"
#include "GUI.h"
#include "GAME.h"

int main()
{
    srand(static_cast<unsigned>(time(0)));

    GAME game;
    game.run();

    //End of application
    return 0;
}