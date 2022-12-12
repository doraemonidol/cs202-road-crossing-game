#pragma once

class SMALL_MONSTER : public MONSTER {
public:
	SMALL_MONSTER();
	SMALL_MONSTER(int dir, int pos, int height);
	void render(sf::RenderTarget &target);
	void update();
	const sf::Vector2f &getPos() const;
};
