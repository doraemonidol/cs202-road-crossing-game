#pragma once

class TRAFFICLIGHT{
private:
	sf::Sprite sprite;
	sf::Texture texture;
    ANIMATION anim;
	int height;
	bool isRed, isBeginning;
public:
	TRAFFICLIGHT(int height);
    TRAFFICLIGHT(float posX, float posY,
        bool isRed, bool isBeginning, int curImgX, int curImgY, float totalTime);
	void render(sf::RenderTarget &target);
	void update();
    void updateAnim(float deltaTime);
	sf::Sprite getSprite();
	bool isRedLight();
	int getHeight();
	void saveGame(std::string fileName);
};

