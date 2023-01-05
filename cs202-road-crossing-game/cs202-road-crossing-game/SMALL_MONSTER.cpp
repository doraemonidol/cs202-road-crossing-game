
#include "main.h"

SMALL_MONSTER::SMALL_MONSTER(int dir, ENEMY_BASE* base)
    : MONSTER(dir, base)
{
}

void SMALL_MONSTER::render(sf::RenderTarget &target){
	target.draw(this->sprite);
}

void SMALL_MONSTER::update(){
	this->sprite.move(this->speed * dir, 0);
}

void SMALL_MONSTER::saveGame(std::string fileName)
{
    std::ofstream file;
    file.open(fileName, std::ios::app);
    file << "\n" << SMALLMONSTER << " ";
    file.close();
    MONSTER::saveGame(fileName);
}
