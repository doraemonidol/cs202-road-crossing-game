#pragma once
#define NEXT_LEVEL_SPEED 2.5f
#define PORTAL_POSITION sf::Vector2f(SCREEN_WIDTH / 3 * 2, SCREEN_HEIGHT / 2)
#define SIDEVIEW_POSITION sf::Vector2f(sideview.getGlobalBounds().width, SCREEN_HEIGHT / 2)
#define PORTAL_DEPTH 25
enum Scene;
class SCENE_MANAGER {
private:
    std::map<std::string, sf::Texture> textures;
    sf::Sprite sideview, portal, finalSprite;
    sf::View* view;
    bool atPortal = false, passedPortal = false, doneLanding = false;
    int playCnt;
    // Animation
    ANIMATION sideviewAnim, portalAnim, landingAnim, finalAnim;

    // Private functions
    void initVariables();
    void initTexture();
    void initSprite();

public:
    SCENE_MANAGER();
    ~SCENE_MANAGER();

    void attachView(sf::View* view);

    void resetNextLevel();

    bool updateNextLevel(float deltaTime);
    bool updateFinalScene(float deltaTime);
    bool update(int worldBGTexY, float deltaTime, int scene);
    void render(sf::RenderTarget& target, int scene);
    void initAfterLoad();
    void renderNextLevel(sf::RenderTarget& target);
    void renderFinalScene(sf::RenderTarget& target);
    void saveGame(std::string fileName);
};
