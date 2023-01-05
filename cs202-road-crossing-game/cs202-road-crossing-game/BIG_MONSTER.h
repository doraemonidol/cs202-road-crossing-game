#pragma once

class BIG_MONSTER : public MONSTER {
public:
	//BIG_MONSTER();
    BIG_MONSTER(int dir, ENEMY_BASE* base);
    ~BIG_MONSTER() {};
	void render(sf::RenderTarget &target);
    void update();
    void saveGame(std::string fileName);
};
