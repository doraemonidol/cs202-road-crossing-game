
#include "main.h"

void GUI::initBG()
{
    if (!this->worldBackgroundTex.loadFromFile("Textures/background.png")) {
        std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE"
                  << "\n";
    }

    this->worldBackground.setTexture(this->worldBackgroundTex);
    this->worldBackground.move(sf::Vector2f(0, (this->worldBackgroundTex.getSize().y - SCREEN_HEIGHT) / (-1.0)));
}

void GUI::initTextures()
{
    this->textures["FULL HEART"] = new sf::Texture();
    this->textures["FULL HEART"]->loadFromFile("Textures/heart-full.png");
    this->textures["EMPTY HEART"] = new sf::Texture();
    this->textures["EMPTY HEART"]->loadFromFile("Textures/heart-empty.png");
    this->textures["LOSE TITLE"] = new sf::Texture();
    this->textures["LOSE TITLE"]->loadFromFile("Textures/lose-text.png");
    this->textures["WIN TITLE"] = new sf::Texture();
    this->textures["WIN TITLE"]->loadFromFile("Textures/win-text.png");
}

void GUI::initGUI()
{
    sf::Color color[] = { sf::Color::White, sf::Color(248, 208, 146), sf::Color(248, 208, 146) };
    //Load font
    if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
        std::cout << "ERROR::GAME::Failed to load font"
                  << "\n";

    //Init level text
    this->levelText.setFont(this->font);
    this->levelText.setCharacterSize(25);
    this->levelText.setFillColor(sf::Color::White);
    this->levelText.setString("Level: xx");
    this->levelText.setOrigin(this->levelText.getGlobalBounds().width / 2, this->levelText.getGlobalBounds().height / 2);
    this->levelText.setPosition(SCREEN_WIDTH / 2, 10.f);

    // Load font
    if (!this->font2.loadFromFile("Fonts/PressStart2P-Regular.ttf"))
        std::cout << "ERROR::GAME::Failed to load font"
                  << "\n";

    // Init TOTAL TIME text
    this->totalTimeText.setFont(this->font2);
    this->totalTimeText.setCharacterSize(35);
    this->totalTimeText.setFillColor(sf::Color::White);
    this->totalTimeText.setString("0.00");
    this->totalTimeText.setOrigin(this->totalTimeText.getGlobalBounds().width / 2, this->totalTimeText.getGlobalBounds().height / 2);
    this->totalTimeText.setPosition(TIME_POSITION.x, TIME_POSITION.y);

    loseTitle.setTexture(*this->textures["LOSE TITLE"]);
    loseTitle.setPosition(this->window->getSize().x / 2.f - this->loseTitle.getGlobalBounds().width / 2.f,
                          this->window->getSize().y / 2.f - this->loseTitle.getGlobalBounds().height / 2.f);

    this->loseText.setFont(this->font);
    this->loseText.setCharacterSize(25);
    this->loseText.setFillColor(sf::Color::White);
    this->loseText.setString("  Sometimes by losing a battle\nyou find a new way to win the war.");
                            //you find a new way to win the war.

    this->loseText.setPosition(
        this->window->getSize().x / 2.f - this->loseText.getGlobalBounds().width / 2.f,
        this->window->getSize().y / 2.f - this->loseText.getGlobalBounds().height / 2.f - loseTitle.getGlobalBounds().height);
    loseMenu = new OPTIONS();
    loseMenu->addButton("Retry", "PressStart2P-Regular.ttf", 21, "pointer.png", color, 0);
    loseMenu->addButton("Back to menu", "PressStart2P-Regular.ttf", 21, "pointer.png", color, 1);
    this->loseMenu->tidyButtons(10);
    // this->loseMenu->setPos(sf::Vector2f(0, 0));
    this->loseMenu->init();


    winTitle.setTexture(*this->textures["WIN TITLE"]);
    winTitle.setPosition(this->window->getSize().x / 2.f - this->winTitle.getGlobalBounds().width / 2.f,
                         this->window->getSize().y / 2.f - this->winTitle.getGlobalBounds().height / 2.f);

    this->winText.setFont(this->font);
    this->winText.setCharacterSize(25);
    this->winText.setFillColor(sf::Color::White);
    this->winText.setString("        Winning isn't everything,\nbut it beats anythingthat comes in second!");
                        //   but it beats anythingthat comes in second.
    this->winText.setPosition(
        this->window->getSize().x / 2.f - this->winText.getGlobalBounds().width / 2.f,
        this->window->getSize().y / 2.f - this->winText.getGlobalBounds().height / 2.f - winTitle.getGlobalBounds().height);
    winMenu = new OPTIONS;
    winMenu->addButton("Continue", "PressStart2P-Regular.ttf", 21, "pointer.png", color, 0);
    winMenu->addButton("Back to menu", "PressStart2P-Regular.ttf", 21, "pointer.png", color, 1);
    this->winMenu->tidyButtons(10);
    // this->winMenu->setPos(sf::Vector2f(0, 0));
    this->winMenu->init();

    //Init pause text
    this->pauseText.setFont(this->font);
    this->pauseText.setCharacterSize(15);
    this->pauseText.setFillColor(sf::Color::White);
    this->pauseText.setString("Press Escape to pause the game");
    this->pauseText.setPosition(5.0f, this->window->getSize().y-20.0f);

    this->pauseMenu = new OPTIONS;
    this->pauseMenu->addButton("Continue", "PressStart2P-Regular.ttf", 21, "pointer.png", color, BACKTOGAME);
    this->pauseMenu->addButton("Restart", "PressStart2P-Regular.ttf", 21, "pointer.png", color, RESTART);
    this->pauseMenu->addButton("Save game", "PressStart2P-Regular.ttf", 21, "pointer.png", color, SAVEGAME);
    this->pauseMenu->addButton("Leaderboard", "PressStart2P-Regular.ttf", 21, "pointer.png", color, LEADERBOARD);
    this->pauseMenu->addButton("Back to menu", "PressStart2P-Regular.ttf", 21, "pointer.png", color, BACKTOMENU);

    this->pauseMenu->tidyButtons(10);
    //this->pauseMenu->setPos(sf::Vector2f(0, 0));
    this->pauseMenu->init();

    this->ingameGUI = new OPTIONS;
    this->ingameGUI->addButton(new BUTTON("mute-anim.png", sf::Vector2u(3, 2), 0.1f, sf::Vector2f(660, 40), 0));
    this->ingameGUI->addButton(new BUTTON("how-anim.png", sf::Vector2u(3, 2), 0.1f, sf::Vector2f(710, 40), 1));
    this->ingameGUI->addButton(new BUTTON("pause-anim.png", sf::Vector2u(3, 2), 0.1f, sf::Vector2f(760, 40), 2));

    //Init player GUI
    if (!bulletBarTexture.loadFromFile("Textures/bullet-bar-2x.png")) {
        std::cout << "ERROR::GUI::GUI::BULLETBAR::Could not load texture file.\n";
    }
    bulletBarControl.initAnim(&this->bulletBarTexture, sf::Vector2u(1, 6), 0);
    bulletBar.setTexture(bulletBarTexture);
    bulletBar.setTextureRect(bulletBarControl.uvRect);
    this->updateBulletBar(5);
}

//Con/Des
GUI::GUI(sf::RenderWindow* window, SPACESHIP * player)
{
    this->window = window;
    this->player = player;
    this->initTextures();
    this->initBG();
    this->initGUI();;
}
GUI::GUI()
{
    this->window = window;
    this->player = player;
    this->initTextures();
    this->initBG();
    this->initGUI();
}

GUI::~GUI()
{
    //Delete textures
    for (auto& i : this->textures) {
        delete i.second;
    }
}

void GUI::resetGUI()
{
    this->levelText.setPosition(700.f, 10.f);
    this->totalTimeText.setPosition(TIME_POSITION.x, TIME_POSITION.y);
    loseTitle.setPosition(this->window->getSize().x / 2.f - this->loseTitle.getGlobalBounds().width / 2.f,
        this->window->getSize().y / 2.f - this->loseTitle.getGlobalBounds().height / 2.f);
    this->loseText.setPosition(
        this->window->getSize().x / 2.f - this->loseText.getGlobalBounds().width / 2.f,
        this->window->getSize().y / 2.f - this->loseText.getGlobalBounds().height / 2.f - loseTitle.getGlobalBounds().height);
    winTitle.setPosition(this->window->getSize().x / 2.f - this->winTitle.getGlobalBounds().width / 2.f,
        this->window->getSize().y / 2.f - this->winTitle.getGlobalBounds().height / 2.f);
    this->winText.setPosition(
        this->window->getSize().x / 2.f - this->winText.getGlobalBounds().width / 2.f,
        this->window->getSize().y / 2.f - this->winText.getGlobalBounds().height / 2.f - winTitle.getGlobalBounds().height);
    this->pauseText.setPosition(5.0f, this->window->getSize().y - 20.0f);
}

float GUI::getDisplacement()
{
    float y = player->getPos().y - SCREEN_HEIGHT / 2;
    if (player->getPos().y > SCREEN_HEIGHT / 2)
        y = 0;
    else {
        int tmp = (SCREEN_HEIGHT - (int)this->worldBackgroundTex.getSize().y);
        if (player->getPos().y < SCREEN_HEIGHT / 2 + tmp)
            y = tmp;
    }
    return y;
}

sf::Vector2u GUI::getBGSize() {
    return (this->worldBackgroundTex.getSize());
}

sf::Sprite GUI::getSprite()
{
    return this->worldBackground;
}

void GUI::updateBulletBar(int bullet)
{
    float y = this->getDisplacement();
    this->bulletBarControl.setCurImg(sf::Vector2u(0, 5 - bullet));
    bulletBar.setTextureRect(bulletBarControl.uvRect);
    this->bulletBar.setPosition(sf::Vector2f(20, y + 20.f));
}

void GUI::updateLevel(int level)
{
    std::stringstream ss;

    ss << "Level: " << level;

    this->levelText.setString(ss.str());
    this->levelText.setOrigin(this->levelText.getGlobalBounds().width / 2, this->levelText.getGlobalBounds().height / 2);
    float y = this->getDisplacement();
    this->levelText.setPosition(SCREEN_WIDTH / 2, y + 10.f);
}

void GUI::updateTime(float totalTime)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << totalTime;

    this->totalTimeText.setString(ss.str());
    this->totalTimeText.setOrigin(this->totalTimeText.getGlobalBounds().width / 2, this->totalTimeText.getGlobalBounds().height / 2);
    float y = this->getDisplacement();
    this->totalTimeText.setPosition(TIME_POSITION.x, y + TIME_POSITION.y);
}

void GUI::update(int level, int bullet, float totalTime)
{
    this->updateLevel(level);
    this->updateTime(totalTime);
    this->updateBulletBar(bullet);
    //this->updateGamePause();
}

void GUI::renderBG()
{
    this->window->draw(this->worldBackground);
}

void GUI::renderBulletBar()
{
    this->window->draw(bulletBar);
}


void GUI::render()
{
    this->window->draw(this->levelText);
    this->window->draw(this->totalTimeText);
    //this->renderGamePause();
    this->renderIngameGUI();
    this->renderBulletBar();
    
}

void GUI::updateGamePause()
{
    float y = this->getDisplacement();
    pauseText.setPosition(10, SCREEN_HEIGHT - pauseText.getGlobalBounds().height - 10 - y);
}

void GUI::renderGamePause()
{
    this->window->draw(pauseText);
}
void GUI::initPauseMenu()
{
    pauseMenuDisplacement = this->getDisplacement();
    this->pauseMenu->movePos(sf::Vector2f(0, pauseMenuDisplacement));
    this->pauseMenu->unpdateButtonDisplacement(sf::Vector2f(0, pauseMenuDisplacement));
    this->pauseMenu->init();
    pauseMenu->draw(window);
}

int GUI::updatePauseMenu(sf::Event e, GAME* gm)
{
    return pauseMenu->update(window, e, gm);
}

void GUI::renderPauseMenu()
{
    pauseMenu->draw(window);
}

void GUI::closePauseMenu() 
{
    this->pauseMenu->movePos(sf::Vector2f(0, -pauseMenuDisplacement));
    this->pauseMenu->unpdateButtonDisplacement(sf::Vector2f(0, 0));
}

void GUI::initLose()
{
    winLoseDisplacement = this->getDisplacement() + 100;
    this->loseMenu->movePos(sf::Vector2f(0, winLoseDisplacement));
    this->loseMenu->unpdateButtonDisplacement(sf::Vector2f(0, winLoseDisplacement - 100));
    this->loseMenu->init();
    loseMenu->draw(window);
}

int GUI::updateLoseMenu(sf::Event e, GAME* gm)
{
    return loseMenu->update(window, e, gm);
}

void GUI::renderLose()
{
    float y = this->getDisplacement();

    loseTitle.setPosition(loseTitle.getPosition().x, SCREEN_HEIGHT / 2 - loseTitle.getGlobalBounds().height + y - 30);
    this->window->draw(loseTitle);

    loseText.setPosition(loseText.getPosition().x, loseTitle.getPosition().y + loseTitle.getGlobalBounds().height - 25);
    this->window->draw(this->loseText);

    loseMenu->draw(window);
}

void GUI::closeLose()
{
    this->loseMenu->movePos(sf::Vector2f(0, -winLoseDisplacement));
    this->loseMenu->unpdateButtonDisplacement(sf::Vector2f(0, 0));
}

void GUI::initWin()
{
    winLoseDisplacement = this->getDisplacement() + 400;
    //std::cout << winLoseDisplacement << "<< here\n";
    this->winMenu->movePos(sf::Vector2f(0, winLoseDisplacement));
    this->winMenu->unpdateButtonDisplacement(sf::Vector2f(0, winLoseDisplacement - 100));
    this->winMenu->init();
}

int GUI::updateWinMenu(sf::Event e, GAME* gm)
{
    return winMenu->update(window, e, gm);
}

void GUI::renderWin()
{
    winTitle.setPosition(winTitle.getPosition().x, SCREEN_HEIGHT / 2 - winTitle.getGlobalBounds().height - 25);
    this->window->draw(winTitle);

    winText.setPosition(winText.getPosition().x, winTitle.getPosition().y + winTitle.getGlobalBounds().height - 25);
    this->window->draw(this->winText);

    winMenu->draw(window);
}

void GUI::closeWin()
{
    std::cout << winLoseDisplacement << "\n";
    this->winMenu->movePos(sf::Vector2f(0, -winLoseDisplacement));
    this->winMenu->unpdateButtonDisplacement(sf::Vector2f(0, 0));
}

int GUI::updateIngameGUI(sf::Event e, GAME* gm)
{
    return ingameGUI->update(window, e, gm);
}

int GUI::updateIngameGUIAnim(GAME* gm)
{
    return ingameGUI->updateAnim(gm);
}

void GUI::renderIngameGUI()
{
    //std::cout << "rendering\n";
    float y = this->getDisplacement();
    this->ingameGUI->movePos2(sf::Vector2f(0, y));
    ingameGUI->draw(window);
}

void GUI::setWorldBackground(sf::Texture* bg)
{
    this->worldBackground.move(sf::Vector2f(0, (this->worldBackgroundTex.getSize().y - SCREEN_HEIGHT) / (1.0)));
    worldBackgroundTex = *bg;
    worldBackground.setTexture(*bg);
    this->worldBackground.move(sf::Vector2f(0, (this->worldBackgroundTex.getSize().y - SCREEN_HEIGHT) / (-1.0)));
}

void GUI::saveGame(std::string fileName) {
    /*std::ofstream file;
    file.open(fileName, std::ios::app);
    file.write((char*)&pauseMenuDisplacement, sizeof(float));
    file.write((char*)&winLoseDisplacement, sizeof(float));
    file.write((char*)&ingameGUIDisplacement, sizeof(float));
    file.close();*/
}