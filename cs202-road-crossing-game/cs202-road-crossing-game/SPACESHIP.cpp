#include "OBSTACLE.h"
#include "UFO.h"
#include "LASER.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "main.h"
#include "GAME.h"
#include "SPACESHIP.h"

void SPACESHIP::initVariables()
{
    this->movementSpeed = 1.f;
    this->speed = 150;

    this->attackCooldownMax = 10.f;
    this->attackCooldown = this->attackCooldownMax;

    this->hpMax = 3;
    this->hp = this->hpMax;
    this->sprite.setPosition(400, 600);

    this->row = 0;
    this->faceRight = true;
}

void SPACESHIP::initTexture()
{
    //Load a texture from file
    if (!this->textures["SPACESHIP"].loadFromFile("Textures/player-anim.png")) {
        std::cout << "ERROR::SPACESHIP::INITTEXTURE::Could not load texture file."
            << "\n";
    }
    if (!this->textures["BLOWUPEFFECT"].loadFromFile("Textures/blow-up-anim.png")) {
        std::cout << "ERROR::SPACESHIP::INITTEXTURE::Could not load texture file."
                  << "\n";
    }
}

void SPACESHIP::initSprite()
{
    //Set the texture to the sprite
    this->sprite.setTexture(this->textures["SPACESHIP"]);
    this->blowupSprite.setTexture(this->textures["BLOWUPEFFECT"]);
    //Resize the sprite
    this->sprite.scale(2.0f, 2.0f);
    this->blowupSprite.scale(2.0f, 2.0f);
}

SPACESHIP::SPACESHIP()
    : anim()
{
    this->initVariables();
    this->initTexture();
    this->initSprite();
    this->anim.initAnim(&this->textures["SPACESHIP"], this->imgCnt, this->switchTime);
    this->blowup.initAnim(&this->textures["BLOWUPEFFECT"], {5, 1}, 0.3);
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

void SPACESHIP::updateInput(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);

    //Move player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        movement.x -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        movement.x += speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        movement.y -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        movement.y += speed * deltaTime;

    if (movement.x == 0.0f) {
        row = 0;
    } else {
        row = 1;

        if (movement.x > 0.0f)
            faceRight = true;
        else
            faceRight = false;
    }

    //this->anim.Update(row, deltaTime, faceRight);
    this->sprite.setTextureRect(anim.uvRect);
    this->move(movement.x, movement.y);
}
//Functions
void SPACESHIP::update(int worldBGTexY, float deltaTime)
{
    this->updateInput(deltaTime);
    this->updateAttack();
    this->updateCollision(worldBGTexY);
    this->anim.Update(row, deltaTime, faceRight);
}

void SPACESHIP::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}

void SPACESHIP::initAfterLoad() {
    this->initTexture();
    this->initSprite();
}

bool SPACESHIP::upDead(float deltaTime)
{
    if (this->blowup.Update(0, deltaTime, true))
        return true;
    this->blowupSprite.setTextureRect(blowup.uvRect);
    sf::Vector2f spaceshipPos = this->sprite.getPosition();
    this->blowupSprite.setPosition({ spaceshipPos.x - 5, spaceshipPos.y - 5 });
    return false;
}

void SPACESHIP::renderDead(sf::RenderTarget& target)
{
    target.draw(this->blowupSprite);
}

const sf::Sprite SPACESHIP::getSprite() {
    return sprite;
}
