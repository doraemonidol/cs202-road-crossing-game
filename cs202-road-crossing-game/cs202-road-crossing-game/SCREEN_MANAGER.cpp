#include "main.h"
#include "ANIMATION.h"
#include "SCREEN_MANAGER.h"

void SCENE_MANAGER::initVariables()
{
    atPortal = false;
    passedPortal = false;
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
}

void SCENE_MANAGER::initSprite()
{
    // Set the texture to the sprite
    this->sideview.setTexture(this->textures["SIDEVIEW"]);
    this->portal.setTexture(this->textures["PORTAL"]);

    // Origin
    this->sideview.setOrigin(sideview.getGlobalBounds().width, this->sideview.getGlobalBounds().height / 2);
    this->portal.setOrigin(0.f, this->portal.getGlobalBounds().height / 2);

    // Position the sprite
    this->sideview.setPosition(SIDEVIEW_POSITION);
    this->portal.setPosition(PORTAL_POSITION);
}

SCENE_MANAGER::SCENE_MANAGER()
    : sideviewAnim(), portalAnim()                                       
{
    this->initVariables();
    this->initTexture();
    this->initSprite();
    this->sideviewAnim.initAnim(&this->textures["SIDEVIEW"], { 4, 1 }, 0.2);
    this->portalAnim.initAnim(&this->textures["PORTAL"], { 16, 1 }, 0.2);
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
        // std::cout << "in\n";
        bound.width -= abs(sideview.getGlobalBounds().left - this->portal.getGlobalBounds().left) - PORTAL_DEPTH;
        bound.left = tmp;
    }
    
    this->sideview.setTextureRect(bound);
    return false;
}
// Functions
bool SCENE_MANAGER::update(int worldBGTexY, float deltaTime, int scene)
{
    switch (scene) {
    case NEXTLEVEL:
        return this->updateNextLevel(deltaTime);
        break;
    default:
        break;
    }
    //this->anim.Update(row, deltaTime, faceRight);
}

void SCENE_MANAGER::render(sf::RenderTarget& target, int scene)
{
    switch (scene) {
    case NEXTLEVEL:
        this->renderNextLevel(target);
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
