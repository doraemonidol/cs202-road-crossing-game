#include "OBSTACLE.h"
#include "UFO.h"
#include "METEOR.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "main.h"
#include "GUI.h"
#include "GAME.h"

//Private functions
void GAME::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Crossing the Universe", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void GAME::initView() {
    this->view = sf::View();
    view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void GAME::initTextures()
{
}

void GAME::initSystems()
{
    this->level = 1;
}

void GAME::initPlayer()
{
    this->player = new SPACESHIP();
}

void GAME::initEnemies()
{
    this->spawnTimerMax = 50.f;
    this->spawnTimer = this->spawnTimerMax;
}

void GAME::initGUI() {
    this->gui = new GUI(this->window, this->player);
}
    //Con/Des
GAME::GAME()
{
    this->initPlayer();
    this->initEnemies();

    this->initView();
    this->initWindow();
    this->initTextures();
    this->initSystems();
    this->initGUI();

}

GAME::~GAME()
{
    delete this->window;
    delete this->player;

    //Delete textures
    for (auto& i : this->textures) {
        delete i.second;
    }
}

//Functions
void GAME::run()
{
    while (this->window->isOpen()) {
        deltaTime = clock.restart().asSeconds();
        this->updatePollEvents();

        if (this->player->getHp() > 0)
            this->update();

        this->render();
    }
}

void GAME::updatePollEvents()
{
    sf::Event e;
    while (this->window->pollEvent(e)) {
        if (e.Event::type == sf::Event::Closed)
            this->window->close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            this->window->close();
        }
    }
}

void GAME::updateInput()
{
}

void GAME::updateWorld()
{
}

void GAME::updateView() {
    float y = player->getPos().y;
    if (y > SCREEN_HEIGHT / 2)
        y = SCREEN_HEIGHT / 2;
    int tmp = (SCREEN_HEIGHT - this->gui->getBGSize().y);
    if (y < SCREEN_HEIGHT / 2 + tmp)
        y = SCREEN_HEIGHT / 2 + tmp;

    view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, y));
    this->window->setView(view);
}

void GAME::update()
{
    //std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";
    // this->updateInput();

    this->player->update(this->gui->getBGSize().y, deltaTime);

    this->gui->update(this->level);

    this->updateWorld();

    this->updateView();
}

void GAME::renderWorld()
{
}

void GAME::render()
{
    this->window->clear();

    //Draw world
    this->renderWorld();
    this->gui->render();

    //Draw all the stuffs
    this->player->render(*this->window);

    //Game over screen
    if (this->player->getHp() <= 0)
        this->gui->renderGameOver();

    this->window->display();
}