#include "OBSTACLE.h"
#include "UFO.h"
#include "METEOR.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "main.h"
#include "SPACESHIP.h"
#include "GAME.h"

int OBSTACLE::getHP(){
	return HP;
}

void OBSTACLE::recievedDmg(int dmg){
	HP = std::max(0, HP - dmg);
}