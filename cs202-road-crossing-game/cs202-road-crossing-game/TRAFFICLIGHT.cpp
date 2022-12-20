#include "TRAFFICLIGHT.h"

TRAFFICLIGHT::TRAFFICLIGHT(int pos, int height){
	if(!textureON.loadFromFile("Textures/traffic-light-on.png")){
		std::cout << "ERROR::TRAFFICLIGHT::INITTEXTURE::Could not load texture file.\n";
	}
	if(!textureOFF.loadFromFile("Textures/traffic-light-off.png")){
		std::cout << "ERROR::TRAFFICLIGHT::INITTEXTURE::Could not load texture file.\n";
	}
	this->sprite.setTexture(textureON);
	this->sprite.scale(0.2f, 0.2f);
	this->sprite.setPosition(pos, height);
	this->height = height - 75;
	isRed = false;
}

void TRAFFICLIGHT::render(sf::RenderTarget &target){
	target.draw(this->sprite);
}

void TRAFFICLIGHT::update(){
	isRed = !isRed;
	if(isRed){
		sprite.setTexture(textureOFF);
	}
	else{
		sprite.setTexture(textureON);
	}
}

sf::Sprite TRAFFICLIGHT::getSprite(){
	return sprite;
}

bool TRAFFICLIGHT::isRedLight(){
	return isRed;
}

int TRAFFICLIGHT::getHeight(){
	return height;
}