
#include "main.h"

//BIG_MONSTER::BIG_MONSTER(){
//	if(!this->texture.loadFromFile("Textures/obstacle-2.png")){
//		std::cout << "ERROR::MOSNTER::INITTEXTURE::Could not load texture file.\n";
//	}
//	this->sprite.setTexture(this->texture);
//	this->sprite.scale(1.3f, 1.3f);
//	this->sprite.setPosition(-100, 100);
//	speed = 1.0;
//	dir = 0;
//	height = 100;
//	HP = 100;
//}

BIG_MONSTER::BIG_MONSTER(int dir, ENEMY_BASE* base)
    : MONSTER::MONSTER(dir, base)
{
}

void BIG_MONSTER::render(sf::RenderTarget &target){
	target.draw(this->sprite);
}

void BIG_MONSTER::update(){
	this->sprite.move(speed * dir, 0);
}

void BIG_MONSTER::saveGame(std::string fileName)
{
    std::ofstream file;
    file.open(fileName, std::ios::app);
    file << "\n" << BIGMONSTER << " ";
    file.close();
    MONSTER::saveGame(fileName);
}
