#include "TRAFFICLIGHT.h"

TRAFFICLIGHT::TRAFFICLIGHT(int pos, int height){
	if(!this->texture.loadFromFile("Textures/traffic-light-on.png")){
		std::cout << "ERROR::TRAFFICLIGHT::INITTEXTURE::Could not load texture file.\n";
	}
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.2f, 0.2f);
	this->sprite.setPosition(pos, height);
	this->height = height - 75;
	isRed = false;
}

void TRAFFICLIGHT::render(sf::RenderTarget &target){
	target.draw(this->sprite);
}

void TRAFFICLIGHT::update(){
	if(isRed){
		if(!this->texture.loadFromFile("Textures/traffic-light-off.png")){
			std::cout << "ERROR::TRAFFICLIGHT::INITTEXTURE::Could not load texture file.\n";
		}
	}
	else{
		if(!this->texture.loadFromFile("Textures/traffic-light-on.png")){
			std::cout << "ERROR::TRAFFICLIGHT::INITTEXTURE::Could not load texture file.\n";
		}
	}
}

sf::Sprite TRAFFICLIGHT::getSprite(){
	return sprite;
}
