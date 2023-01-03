
#include "main.h"

void SCENE_MANAGER::initVariables()
{
    atPortal = false;
    passedPortal = false;
    doneLanding = false;
    playCnt = 2;
}

void SCENE_MANAGER::initTexture()
{
    // Load a texture from file
    if (!this->textures["SIDEVIEW"].loadFromFile("Textures/side-view-2x.png")) {
        std::cout << "ERROR::SCREEN_MANAGER::INITTEXTURE::Could not load texture file."
                  << "\n";
    }
    if (!this->textures["PORTAL"].loadFromFile("Textures/portal-2x.png")) {
        std::cout << "ERROR::SCREEN_MANAGER::INITTEXTURE::Could not load texture file."
                  << "\n";
    }
    if (!this->textures["FINAL"].loadFromFile("Textures/final-scene.png")) {
        std::cout << "ERROR::SCREEN_MANAGER::INITTEXTURE::Could not load texture file."
                  << "\n";
    }
}

void SCENE_MANAGER::initSprite()
{
    // Set the texture to the sprite
    this->sideview.setTexture(this->textures["SIDEVIEW"]);
    this->portal.setTexture(this->textures["PORTAL"]);
    this->finalSprite.setTexture(this->textures["FINAL"]);

    // Origin
    this->sideview.setOrigin(sideview.getGlobalBounds().width, this->sideview.getGlobalBounds().height / 2);
    this->portal.setOrigin(0.f, this->portal.getGlobalBounds().height / 2);
    this->finalSprite.setOrigin(finalSprite.getGlobalBounds().width / 32, this->finalSprite.getGlobalBounds().height / 6);

    // Position the sprite
    this->sideview.setPosition(SIDEVIEW_POSITION);
    this->portal.setPosition(PORTAL_POSITION);
    this->finalSprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 32, SCREEN_HEIGHT / 6));
    this->finalSprite.setScale(sf::Vector2f(1.8, 1.8));
}

SCENE_MANAGER::SCENE_MANAGER()
    : sideviewAnim(), portalAnim()                                       
{
    this->initVariables();
    this->initTexture();
    this->initSprite();
    this->sideviewAnim.initAnim(&this->textures["SIDEVIEW"], { 4, 1 }, 0.2);
    this->portalAnim.initAnim(&this->textures["PORTAL"], { 16, 1 }, 0.2);
    this->finalAnim.initAnim(&this->textures["FINAL"], { 16, 3 }, 0.1);
    this->finalAnim.setCurImg(sf::Vector2u(2, 0));
}

SCENE_MANAGER::~SCENE_MANAGER()
{
}

void SCENE_MANAGER::attachView(sf::View* view)
{
    this->view = view;            
}

void SCENE_MANAGER::resetNextLevel()
{
    this->initVariables();
    this->initSprite();
}

bool SCENE_MANAGER::updateNextLevel(float deltaTime)
{
    //std::cout << "IN NEXT LEVEL\n";
    this->portalAnim.Update(0, deltaTime, true);
    this->portal.setTextureRect(portalAnim.uvRect);

    sf::Vector2f prePos = this->sideview.getPosition();

    this->sideview.move(NEXT_LEVEL_SPEED, 0);
    this->sideviewAnim.Update(0, deltaTime, true);
    sf::IntRect bound = sideviewAnim.uvRect;

    if (portal.getGlobalBounds().intersects(sideview.getGlobalBounds())) {
        atPortal = true;
    }
    if (sideview.getGlobalBounds().left - this->portal.getGlobalBounds().left - PORTAL_DEPTH >= bound.width) {
        bound.width = 0;
        return true;
    }
    else if (atPortal && prePos != SIDEVIEW_POSITION &&
        (sideview.getGlobalBounds().left - this->portal.getGlobalBounds().left - PORTAL_DEPTH > 0)) {
        int tmp = bound.left;
        // system("pause");
        bound.width -= abs(sideview.getGlobalBounds().left - this->portal.getGlobalBounds().left) - PORTAL_DEPTH;
        bound.left = tmp;
    }
    
    this->sideview.setTextureRect(bound);
    return false;
}
bool SCENE_MANAGER::updateFinalScene(float deltaTime)
{
    if (!doneLanding) {
        if (playCnt >= 0) {
            playCnt -= this->finalAnim.Update(2, deltaTime, true);
            if (playCnt < 0) {
                this->finalAnim.setCurImg(sf::Vector2u(0, 0));
            }
            this->finalSprite.setTextureRect(finalAnim.uvRect);
        } else {
            // std::cout << "landing \n";
            if (this->finalAnim.Update(0, deltaTime, true)) {
                this->finalAnim.setCurImg(sf::Vector2u(0, 1));
                doneLanding = true;
                return false;
            }
            this->finalSprite.setTextureRect(finalAnim.uvRect);
            // std::cout << finalAnim.getCurImgCnt().x << " ";
        }
    } else {
        //std::cout << "looping \n";
        //std::cout << finalAnim.getCurImgCnt().x << " ";
        this->finalAnim.Update(1, deltaTime, true);
        this->finalSprite.setTextureRect(finalAnim.uvRect);
    }
    this->finalSprite.setScale(sf::Vector2f(1.8, 1.8));
    this->finalSprite.setOrigin(finalSprite.getLocalBounds().width / 2, this->finalSprite.getLocalBounds().height / 2);
    this->finalSprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    return true;
}
// Functions
bool SCENE_MANAGER::update(int worldBGTexY, float deltaTime, int scene)
{
    switch (scene) {
    case NEXTLEVEL:
        return this->updateNextLevel(deltaTime);
        break;
    case ENDGAME:
        this->updateFinalScene(deltaTime);
        break;
    default:
        break;
    }
    return false;
    //this->anim.Update(row, deltaTime, faceRight);
}

void SCENE_MANAGER::render(sf::RenderTarget& target, int scene)
{
    switch (scene) {
    case NEXTLEVEL:
        this->renderNextLevel(target);
        break;
    case ENDGAME:
        this->renderFinalScene(target);
        break;
    default:
        break;
    }
   // target.draw(this->sprite);
}

void SCENE_MANAGER::initAfterLoad()
{
    this->initTexture();
    this->initSprite();
}

void SCENE_MANAGER::renderNextLevel(sf::RenderTarget& target)
{
    target.draw(this->portal);
    target.draw(this->sideview);
}

void SCENE_MANAGER::renderFinalScene(sf::RenderTarget& target)
{
    //std::cout << "renderring final sprite \n";
    target.draw(this->finalSprite);
}

void SCENE_MANAGER::saveGame(std::string fileName) {
    std::ofstream file;
    file.open(fileName, std::ios::app);
    if (!file) {
        std::cout << "Unable to open save game!" << std::endl;
        return;
    }
    file.write((char*)&sideview.getPosition().x, sizeof(float));
    file.write((char*)&sideview.getPosition().y, sizeof(float));
    file.write((char*)&portal.getPosition().x, sizeof(float));
    file.write((char*)&portal.getPosition().y, sizeof(float)); 
    file.write((char*)&finalSprite.getPosition().x, sizeof(float));
    file.write((char*)&finalSprite.getPosition().y, sizeof(float));
    file.write((char*)view, sizeof(sf::View));
    file.write((char*)&atPortal, sizeof(bool));
    file.write((char*)&passedPortal, sizeof(bool));
    file.write((char*)doneLanding, sizeof(bool));
    file.write((char*)playCnt, sizeof(int));
    file.close();
    sideviewAnim.saveGame(fileName);
    portalAnim.saveGame(fileName);
    landingAnim.saveGame(fileName);
    finalAnim.saveGame(fileName);

}