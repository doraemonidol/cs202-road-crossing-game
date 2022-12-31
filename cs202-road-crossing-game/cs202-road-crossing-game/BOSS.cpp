#include "BOSS.h"

BOSS::BOSS() {
    initAnimation();
    initSprite();
    initVariables();
}

BOSS::~BOSS()
{
}

void BOSS::initAnimation()
{
    if (!texture[IDLE].loadFromFile(BOSS_TEXTURE_IDLE)) {
        std::cout << "ERROR::BOSS::INITTEXTURE::IDLE::Could not load texture file."
                  << "\n";
    }
    anim[IDLE].initAnim(&texture[IDLE], sf::Vector2u(4, 1), 0.2);
    if (!texture[SHOOT_4].loadFromFile(BOSS_TEXTURE_SHOOT1)) {
        std::cout << "ERROR::BOSS::INITTEXTURE::SHOOT1::Could not load texture file."
                  << "\n";
    }
    anim[SHOOT_4].initAnim(&texture[SHOOT_4], sf::Vector2u(6, 1), 0.2);
    if (!texture[SHOOTLASER].loadFromFile(BOSS_TEXTURE_SHOOT2)) {
        std::cout << "ERROR::BOSS::INITTEXTURE::SHOOT2::Could not load texture file."
                  << "\n";
    }
    anim[SHOOTLASER].initAnim(&texture[SHOOTLASER], sf::Vector2u(4, 1), 0.2);
    if (!texture[SHOOTLASER].loadFromFile(BOSS_TEXTURE_SHOOT2)) {
        std::cout << "ERROR::BOSS::INITTEXTURE::SHOOT2::Could not load texture file."
                  << "\n";
    }
    anim[SHOOTLASER].initAnim(&texture[SHOOTLASER], sf::Vector2u(4, 1), 0.2);

    if (!dieTexture.loadFromFile(BOSS_TEXTURE_DIE)) {
        std::cout << "ERROR::BOSS::INITTEXTURE::DIE::Could not load texture file."
                  << "\n";
    }
    dieAnim.initAnim(&dieTexture, sf::Vector2u(8, 1), 0.125);
}

void BOSS::initSprite()
{
    speed = BOSS_NORMAL_SPEED;
    hp = 100;

    pos = sf::Vector2f(SCREEN_WIDTH / 2, -10); // SCREEN_HEIGHT + sprite.getGlobalBounds().height);
    sprite.setTexture(texture[IDLE]);
    sprite.setTextureRect(anim[IDLE].uvRect);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, 0);
    sprite.setPosition(pos);

    dieSprite.setTexture(dieTexture);
    dieSprite.setTextureRect(dieAnim.uvRect);
    dieSprite.setOrigin(dieSprite.getGlobalBounds().width / 2, 0);
}

void BOSS::initVariables()
{
    isPlaying = false;
    bullets.clear();
    deadDir = 1;
    whiteDuration = 2;

    shooter[2] = sf::Vector2f(pos.x - 90, 40);
    shooter[1] = sf::Vector2f(pos.x + 20, 55);
    shooter[0] = sf::Vector2f(pos.x - 20, 145);
    shooter[3] = sf::Vector2f(pos.x + 90, 160);

    laserCollider.setSize(sf::Vector2f(14, 500));
    laserCollider.setOrigin(sf::Vector2f(laserCollider.getGlobalBounds().width / 2, 0));
    laserCollider.setPosition(sf::Vector2f(sprite.getPosition().x, 120));

    laserCollider.setFillColor(sf::Color::Transparent);
    laserCollider.setOutlineColor(sf::Color::White);
    laserCollider.setOutlineThickness(2);

    bossCollider.setSize(sf::Vector2f(140, 140));
    bossCollider.setOrigin(sf::Vector2f(bossCollider.getGlobalBounds().width / 2, 0));
    bossCollider.setPosition(sf::Vector2f(sprite.getPosition().x, 10));

    bossCollider.setFillColor(sf::Color::Transparent);
    bossCollider.setOutlineColor(sf::Color::White);
    bossCollider.setOutlineThickness(2);

    dieOverlay.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    dieOverlay.setOrigin(sf::Vector2f(dieOverlay.getGlobalBounds().width / 2, dieOverlay.getGlobalBounds().height / 2));
    dieOverlay.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

    dieOverlay.setFillColor(sf::Color(0,0,0,0));
}

void BOSS::receiveDmg(int dmg)
{
    this->hp = std::max(0, this->hp - dmg);
}

bool BOSS::updead(float deltaTime)
{
    if (deadDir == 1) {
        if (dieAnim.Update(0, deltaTime, true)) {
            dieOverlay.setFillColor(sf::Color::White);
            deadDir = -1;
            return false;
        }
    
        dieSprite.setTextureRect(dieAnim.uvRect);
        dieSprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 300);

        int a = dieOverlay.getFillColor().a;
        dieOverlay.setFillColor(sf::Color(255, 255, 255, std::min(255.f, a + 255 * deltaTime * deadDir)));
        return false;
    }

    whiteDuration -= deltaTime;
    if (whiteDuration > 0)
        return false;

    int a = dieOverlay.getFillColor().a;

    if (a == 0)
        return true;

    dieOverlay.setFillColor(sf::Color(255, 255, 255, std::max(0.f, a + 255 * 2 * deltaTime * deadDir)));
    return false;
}

void BOSS::updateBullets()
{
    this->removeBullet();
    // Update and render bullet
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->update();
    }
}

void BOSS::updateShooterPos()
{
    pos = this->sprite.getPosition();
    shooter[2] = sf::Vector2f(pos.x - 115, shooter[2].y);
    shooter[1] = sf::Vector2f(pos.x + 95, shooter[1].y);
    shooter[0] = sf::Vector2f(pos.x - 115, shooter[0].y);
    shooter[3] = sf::Vector2f(pos.x + 95, shooter[3].y);
}

void BOSS::updateLaserPos()
{
    laserCollider.setPosition(sf::Vector2f(sprite.getPosition().x - 7, laserCollider.getPosition().y));
}

void BOSS::updateBossCollider()
{
    bossCollider.setPosition(sf::Vector2f(sprite.getPosition().x - 7, bossCollider.getPosition().y));
}

bool BOSS::update(float deltaTime, sf::Vector2f playerPos)
{
    if (isDead()) {
        return updead(deltaTime);
    }
    if (!isPlaying) {
        if (curState != IDLE)
            curState = IDLE;
        else {
            curState = rand() % (bossStateCnt + 2);
        }

        if (curState >= bossStateCnt)
            curState = IDLE;
        isPlaying = true;
        anim[curState].setCurImg(sf::Vector2u(0, 0));
        shooted.assign(4, false);
        //std::cout << "new boss state " << curState <<"\n";
        sprite.setTexture(texture[curState]);
        sprite.setTextureRect(anim->uvRect);

        switch (curState) {
        case SHOOT_4:
            speed = BOSS_SHOOTING_SPEED;
            break;
        default:
            break;
        }
    }
    updateBullets();
    updateShooterPos();
    updateLaserPos();
    updateBossCollider();
    //for (int i = 0; i < 4; i++) {
    //    rec[i].setSize(sf::Vector2f(4, 4));
    //    rec[i].setFillColor(sf::Color::Transparent);
    //    rec[i].setOutlineColor(sf::Color::White);
    //    rec[i].setOutlineThickness(2);
    //    rec[i].setPosition(shooter[i]);
    //    rec[i].setOrigin(2, 2);
    //}

    isPlaying = !anim[curState].Update(0, deltaTime, true);
    sprite.setTextureRect(anim[curState].uvRect);
    int curImg = anim[curState].getCurImgCnt().x;
    switch (curState) {
    case SHOOT_4:
        if (!isPlaying)
            speed = BOSS_NORMAL_SPEED;
        move(playerPos);
        if (curImg == 0 || curImg > 4 || shooted[curImg - 1])
            break;
        shooted[curImg - 1] = true;
        shootRatata(shooter[curImg - 1]);
    case SHOOTLASER:
        break;
    default:
        move(playerPos);
        break;
    }

    //int newState = curState;

    //sprite.setTexture(texture[curState]);
    //sprite.setTextureRect(anim[curState].uvRect);
    return false;
}

void BOSS::renderDead(sf::RenderTarget& target)
{
    target.draw(dieOverlay);
    if (deadDir == 1)
        target.draw(dieSprite);
}

void BOSS::renderBullets(sf::RenderTarget& target)
{
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->render(target);
    }
}

void BOSS::render(sf::RenderTarget& target)
{
    if (deadDir == 1) {
        target.draw(sprite);
        renderBullets(target);
    }
    if (isDead()) {
        renderDead(target);
        return;
    }
    //target.draw(rec[0]);
    //target.draw(rec[1]);
    //target.draw(rec[2]);
    //target.draw(rec[3]);
    //target.draw(laserCollider);
    //target.draw(bossCollider);
}

void BOSS::move(sf::Vector2f dest)
{
    dest = sf::Vector2f(dest.x + 40, dest.y);
    float dis = dest.x - this->sprite.getPosition().x;
    if (dis == 0)
        return;
    //std::cout << dis << " " << dest.x << " " << this->sprite.getPosition().x
    //          << "\n";
    this->sprite.move(this->speed * (dis / abs(dis)), 0);
}

void BOSS::shootRatata(sf::Vector2f pos)
{
    this->bullets.push_back(new BULLET(pos, 1));
}

void BOSS::removeBullet()
{
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i]->getMoveLength() == 0) {
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }
}

void BOSS::shootLaser(float)
{
}

bool BOSS::isCollide(sf::FloatRect obj)
{
    if (deadDir == -1)
        return false;
    if (bossCollider.getGlobalBounds().intersects(obj))
        return true;

    if (curState == SHOOTLASER && anim[curState].getCurImgCnt().x >= 2 && anim[curState].getCurImgCnt().x <= 3 && laserCollider.getGlobalBounds().intersects(obj))
        return true;

    for (int i = 0; i < bullets.size(); i++) {
        // std::cout << i << "\n";
        if (bullets[i]->getSprite().getGlobalBounds().intersects(obj))
            return true;
    }
    return false;
}

bool BOSS::isShoot(sf::FloatRect obj)
{
    if (deadDir == -1)
        return false;
    return bossCollider.getGlobalBounds().intersects(obj);
}

bool BOSS::isDead()
{
    return (getHp() <= 0);
}

bool BOSS::stopShowMonster()
{
    return deadDir == -1;
}

void BOSS::reset()
{
    initSprite();
    initVariables();
}

int BOSS::getHp()
{
    return hp;
}
