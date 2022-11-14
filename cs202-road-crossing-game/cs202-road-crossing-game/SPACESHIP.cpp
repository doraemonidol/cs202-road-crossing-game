#include "OBSTACLE.h"
#include "UFO.h"
#include "METEOR.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "main.h"
#include "SPACESHIP.h"
#include "GAME.h"

void SPACESHIP::initVariables()
{
    this->movementSpeed = 1.f;

    this->attackCooldownMax = 10.f;
    this->attackCooldown = this->attackCooldownMax;

    this->hpMax = 3;
    this->hp = this->hpMax;
    this->sprite.setPosition(400, 600);
}

void SPACESHIP::initTexture()
{
    //Load a texture from file
    if (!this->texture.loadFromFile("Textures/player.png")) {
        std::cout << "ERROR::SPACESHIP::INITTEXTURE::Could not load texture file."
                  << "\n";
    }
}

void SPACESHIP::initSprite()
{
    //Set the texture to the sprite
    this->sprite.setTexture(this->texture);

    //Resize the sprite
    this->sprite.scale(2.0f, 2.0f);
}

SPACESHIP::SPACESHIP()
{
    this->initVariables();
    this->initTexture();
    this->initSprite();
}

SPACESHIP::~SPACESHIP()
{
}

const sf::Vector2f& SPACESHIP::getPos() const
{
    return this->sprite.getPosition();
}

const sf::FloatRect SPACESHIP::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const int& SPACESHIP::getHp() const
{
    return this->hp;
}

const int& SPACESHIP::getHpMax() const
{
    return this->hpMax;
}

void SPACESHIP::setPosition(const sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
}

void SPACESHIP::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

void SPACESHIP::setHp(const int hp)
{
    this->hp = hp;
}

void SPACESHIP::loseHp(const int value)
{
    this->hp -= value;
    if (this->hp < 0)
        this->hp = 0;
}

void SPACESHIP::move(const float dirX, const float dirY)
{
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool SPACESHIP::canAttack()
{
    if (this->attackCooldown >= this->attackCooldownMax) {
        this->attackCooldown = 0.f;
        return true;
    }

    return false;
}

void SPACESHIP::updateAttack()
{
    if (this->attackCooldown < this->attackCooldownMax)
        this->attackCooldown += 0.5f;
}

void SPACESHIP::updateCollision(int worldBGTexY)
{
    //Left world collision
    if (this->getBounds().left < 0.f) {
        this->setPosition(0.f, this->getBounds().top);
    }
    //Right world collison
    else if (this->getBounds().left + this->getBounds().width >= SCREEN_WIDTH) {
        this->setPosition(SCREEN_WIDTH - this->getBounds().width, this->getBounds().top);
    }
    //Top world collision
    if (this->getBounds().top + (worldBGTexY - SCREEN_HEIGHT) < 0.f) {
        //std::cout << this->player->getBounds().top << std::endl;
        int y = (SCREEN_HEIGHT - worldBGTexY);
        this->setPosition(this->getBounds().left, y);
    }
    //Bottom world collision
    else if (this->getBounds().top + this->getBounds().height >= SCREEN_HEIGHT + 30) {
        this->setPosition(this->getBounds().left, SCREEN_HEIGHT - this->getBounds().height + 30);
    }
}

void SPACESHIP::updateInput()
{
    //Move player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        this->move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        this->move(1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        this->move(0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        this->move(0.f, 1.f);
}
//Functions
void SPACESHIP::update(int worldBGTexY)
{
    this->updateInput();
    this->updateAttack();
    this->updateCollision(worldBGTexY);
}

void SPACESHIP::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}