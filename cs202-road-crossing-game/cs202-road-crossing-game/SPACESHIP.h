#pragma once 
class SPACESHIP {
private:
    sf::Sprite sprite;
    sf::Texture texture;

    float movementSpeed;

    float attackCooldown;
    float attackCooldownMax;

    int hp;
    int hpMax;

    //Private functions
    void initVariables();
    void initTexture();
    void initSprite();

public:
    SPACESHIP();
    virtual ~SPACESHIP();

    //Accessor
    const sf::Vector2f& getPos() const;
    const sf::FloatRect getBounds() const;
    const int& getHp() const;
    const int& getHpMax() const;

    //Modifiers
    void setPosition(const sf::Vector2f pos);
    void setPosition(const float x, const float y);
    void setHp(const int hp);
    void loseHp(const int value);

    //Functions
    void move(const float dirX, const float dirY);
    const bool canAttack();

    void updateAttack();
    void updateCollision(int worldBGTexY);
    void updateInput();
    void update(int worldBGTexY);
    void render(sf::RenderTarget& target);
};