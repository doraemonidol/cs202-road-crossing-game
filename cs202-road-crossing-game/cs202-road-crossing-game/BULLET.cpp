#include "BULLET.h"

BULLET::BULLET() {
	if (!this->texture.loadFromFile("Textures/bullet.png")) {
		std::cout << "ERROR::BULLET::Could not load texture file.\n";
	}
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.05f, 0.05f);
	this->sprite.setPosition(400, 600);
	this->sprite.setRotation(-90.f);
	this->speed = 6;
	this->damage = 100;
	this->moveLength = 500;
}

BULLET::BULLET(sf::Vector2f pos) {
	if (!this->texture.loadFromFile("Textures/bullet.png")) {
		std::cout << "ERROR::BULLET::Could not load texture file.\n";
	}
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.05f, 0.05f);
	this->sprite.setPosition(pos.x+18, pos.y);
	this->sprite.setRotation(-90.f);
	this->speed = 6;
	this->damage = 100;
	this->moveLength = 500;
}

BULLET::BULLET(sf::Vector2f pos, bool enemy) {
	if(!this->texture.loadFromFile("Textures/bullet.png")) {
		std::cout << "ERROR::BULLET::Could not load texture file.\n";
	}
	this->sprite.setTexture(this->texture);
	this->sprite.scale(0.05f, 0.05f);
	if(!enemy) {
		this->sprite.setPosition(pos.x + 18, pos.y);
		this->sprite.setRotation(-90.f);
		this->speed = 6;
		this->damage = 100;
		this->moveLength = 500;
		isPlayerBullet = true;
	}
	else {
		this->sprite.setPosition(pos.x + 45, pos.y + 60);
		this->sprite.setRotation(90.f);
		this->speed = -6;
		this->damage = 100;
		this->moveLength = 500;
		isPlayerBullet = false;
	}
}

void BULLET::update() {
	this->sprite.move(0, -speed);
	this->moveLength = this->moveLength > 0 ? this->moveLength-- : 0;
}

sf::Vector2f BULLET::getPosition() {
	return this->sprite.getPosition();
}

void BULLET::render(sf::RenderTarget& targer) {
	targer.draw(this->sprite);
}

int BULLET::getDamage() {
	return this->damage;
}

sf::Sprite BULLET::getSprite() {
	return this->sprite;
}

int BULLET::getMoveLength() {
	return this->moveLength;
}

bool BULLET::PlayerBullet() {
	return isPlayerBullet;
}