#include "OBSTACLE.h"
#include "UFO.h"
#include "METEOR.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "main.h"
#include "GUI.h"
#include "GAME.h"

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
}

void GUI::initGUI()
{
    //Load font
    if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
        std::cout << "ERROR::GAME::Failed to load font"
                  << "\n";

    //Init level text
    this->levelText.setPosition(700.f, 10.f);
    this->levelText.setFont(this->font);
    this->levelText.setCharacterSize(30);
    this->levelText.setFillColor(sf::Color::White);
    this->levelText.setString("test");

    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(60);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("Game Over!");
    this->gameOverText.setPosition(
        this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
        this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

    //Init pause text
    this->pauseText.setFont(this->font);
    this->pauseText.setCharacterSize(15);
    this->pauseText.setFillColor(sf::Color::White);
    this->pauseText.setString("Press Escape to pause the game");
    this->pauseText.setPosition(5.0f, this->window->getSize().y-20.0f);
    


    //Init player GUI
    this->updateHealth(this->player->getHpMax());
}

//Con/Des
GUI::GUI(sf::RenderWindow* window, SPACESHIP * player)
{
    this->window = window;
    this->player = player;
    this->initTextures();
    this->initBG();
    this->initGUI();
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

    ////Delete bullets
    //for (auto* i : this->bullets) {
    //    delete i;
    //}

    //Delete enemies
    /* for (auto* i : this->enemies) {
        delete i;
    }*/
}

void GUI::updateHealth(int health)
{
    float y = this->getDisplacement();

    for (int i = 1; i <= health; i++) {
        this->playerHp[i].setPosition(sf::Vector2f(20.f + (i - 1) * ((*textures["FULL HEART"]).getSize().x * 2 + 5), y + 20.f));
        this->playerHp[i].setTexture(*textures["FULL HEART"]);
        this->playerHp[i].setScale(2.f, 2.f);
    }
    for (int i = health + 1; i <= this->player->getHpMax(); i++) {
        this->playerHp[i].setPosition(sf::Vector2f(20.f + (i - 1) * ((*textures["EMPTY HEART"]).getSize().x * 2 + 5), y + 20.f));
        this->playerHp[i].setTexture(*textures["EMPTY HEART"]);
        this->playerHp[i].setScale(2.f, 2.f);
    }
}

float GUI::getDisplacement() {
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

void GUI::updateLevel(int level)
{
    std::stringstream ss;

    ss << "Level: " << level;

    this->levelText.setString(ss.str());
    float y = this->getDisplacement();
    this->levelText.setPosition(700.f, y + 10.f);
}

void GUI::update(int level)
{
    this->updateLevel(level);
    this->updateHealth(this->player->getHp());
}

void GUI::renderGameOver() {
    this->window->draw(this->gameOverText);
}

void GUI::render()
{
    this->window->draw(this->worldBackground);
    this->window->draw(this->levelText);
    this->window->draw(this->pauseText);
    for (int i = 1; i <= this->player->getHpMax(); i++) {
        this->window->draw(this->playerHp[i]);
    }
}
