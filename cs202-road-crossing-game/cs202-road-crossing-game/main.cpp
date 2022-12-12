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

           // test.playSound("sound_test/Ambiance.wav");

    srand(static_cast<unsigned>(time(0)));

  /*  sf::Music music;
    if (!music.openFromFile("Sound/background-music.wav")) {
        std::cout << "ERROR\n";
    }
    music.play();*/

    GAME game;
    game.run();

    //End of application
    return 0;
}