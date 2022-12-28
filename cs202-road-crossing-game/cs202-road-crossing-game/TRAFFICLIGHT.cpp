#include "TRAFFICLIGHT.h"

TRAFFICLIGHT::TRAFFICLIGHT(int height){
	if(!texture.loadFromFile("Textures/freeze-laser.png")){
		std::cout << "ERROR::TRAFFICLIGHT::INITTEXTURE::Could not load texture file.\n";
	}
	this->sprite.setTexture(texture);

	anim.initAnim(&texture, sf::Vector2u(24, 2), 0.1f);
    this->sprite.setTextureRect(anim.uvRect);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setPosition(SCREEN_WIDTH / 2, height);
    this->sprite.scale(2.f, 1.f);
	isRed = false;
    isBeginning = true;
}

void TRAFFICLIGHT::render(sf::RenderTarget &target){
    if (isRed)
		target.draw(this->sprite);
}

void TRAFFICLIGHT::update(){
	isRed = !isRed;
    isBeginning = isRed;
    anim.setCurImg(sf::Vector2u(0, 0));
}

void TRAFFICLIGHT::updateAnim(float deltaTime)
{
    if (isRed) {
        if (isBeginning) {
            isBeginning = !anim.Update(0, deltaTime, true);
            if (!isBeginning)
                anim.setCurImg(sf::Vector2u(0, 1));
        } else {
            anim.Update(1, deltaTime, true);
        }
        this->sprite.setTextureRect(anim.uvRect);
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