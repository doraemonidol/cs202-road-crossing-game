#pragma once

class UFO : public OBSTACLE {
public:
	UFO() {
		if (!this->texture.loadFromFile("Textures/obstacle-4.png")) {
			std::cout << "ERROR::MOSNTER::INITTEXTURE::Could not load texture file.\n";
		}
		this->sprite.setTexture(this->texture);
		this->sprite.scale(1.3f, 1.3f);
		this->sprite.setPosition(-100, 100);
		dir = 0;
	}
	UFO (int dir, int pos, int height) {
		if (!this->texture.loadFromFile("Textures/obstacle-4.png")) {
			std::cout << "ERROR::MOSNTER::INITTEXTURE::Could not load texture file.\n";
		}
		this->sprite.setTexture(this->texture);
		this->sprite.scale(1.3f, 1.3f);
		this->sprite.setPosition(pos, height);
		this->dir = dir;
	}
	void render(sf::RenderTarget& target) {

		target.draw(this->sprite);
	}
	void update() {
		this->sprite.move(4.0f * dir, 0);
	}
	const sf::Vector2f& getPos() const
	{
		return this->sprite.getPosition();
	}
};
