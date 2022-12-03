#include "OBSTACLE.h"
#include "UFO.h"
#include "METEOR.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "main.h"
#include "GUI.h"
#include "GAME.h"
#include <iostream>
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
    this->scene = INGAME;
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

void GAME::initMenu() {
    menu = MENU(200, 200);
    menu.init();
}

    //Con/Des
GAME::GAME()
{
    this->isPause = false;

    this->initPlayer();
    this->initEnemies();

    this->initView();
    this->initWindow();
    this->initTextures();
    this->initSystems();
    this->initGUI();
    this->initMenu();
    this->loadGame();

}

GAME::GAME(const int a) {
    this->isPause = false;

    this->initPlayer();
    this->initEnemies();

    this->initView();
    this->initWindow();
    this->initTextures();
    this->initSystems();
    this->initGUI();
    this->initMenu();
    this->loadGame();
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
        if (this->isPause == false) {
            if (this->player->getHp() > 0)
                this->update();
        }
        this->render();
        this->saveGame();
    }
}

void GAME::updatePollEvents()
{
    sf::Event e;
    while (this->window->pollEvent(e)) {
        if (e.Event::type == sf::Event::Closed)
            this->window->close();
        switch (scene) {
        case MENUSCENE:
            menu.update(this->window, e);
            break;
        case INGAME:
            if (e.type == sf::Event::KeyPressed) {
                switch (e.key.code) {
                case sf::Keyboard::Escape:
                    if (this->isPause == false) {
                        this->isPause = true;
                    } else {
                        this->isPause = false;
                    }
                    break;
                // case sf::Keyboard::M :
                //     //Back to menu
                //     break;
                case sf::Keyboard::S:
                    if (this->isPause) {
                    }
                    break;
                // case sf::Keyboard::R :
                //     //replay:
                //     break;
                default:
                    break;
                }
            }
            break;
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
        y = SCREEN_HEIGHT / 2.0f + tmp;

    view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, y));
    this->window->setView(view);
}

void GAME::update()
{
   /* std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";*/
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
    switch (scene) {
    case MENUSCENE:
        this->menu.draw(this->window);
        break;
    case INGAME:
        // Draw world
        this->renderWorld();
        this->gui->render();

        // Draw all the stuffs
        this->player->render(*this->window);

        // Game pause screen:
        if (this->isPause) {
            this->renderGamePause();
        }

        // Game over screen
        if (this->player->getHp() <= 0)
            this->gui->renderGameOver();
        break;
    }

    this->window->display();
}

void GAME::renderGamePause() {
    //Load font
    sf::Font font;
    if (!font.loadFromFile("Fonts/PixellettersFull.ttf"))
        std::cout << "ERROR::GAME::Failed to load font"
        << "\n";
    sf::Text pauseText;
    pauseText.setFont(font);
    pauseText.setCharacterSize(30);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setString("Press S to save game\nPress M to go back to menu\nPress Escape to continue\nPress H to view highscore\nPress R to replay");
    pauseText.setPosition(this->window->getSize().x/2.0f - 130.0f, this->window->getSize().y/2.0f - 70.0f);
    this->window->draw(pauseText);
}

template <class T>void swap(T* a, T* b);

void GAME::saveGame() {
    std::ofstream file;
    file.open("Game.txt", std::ios::out);
    if (!file) {
        std::cout << "Unable to open save game!" << std::endl;
        return;
    }
    /*file.write((char*)window, sizeof(GAME));*/
    file.write((char*)&view, sizeof(sf::View));
    file.write((char*)&isPause, sizeof(bool));
    file.write((char*)&level, sizeof(unsigned));
    file.write((char*)&scene, sizeof(scene));
    file.write((char*)&deltaTime,sizeof(float));
    file.write((char*)&clock, sizeof(sf::Clock));
    file.write((char*)player, sizeof(SPACESHIP));
    /*file.write((char*)gui, sizeof(GUI));*/
    file.write((char*)&menu, sizeof(MENU));
    file.write((char*)&spawnTimer, sizeof(float));
    file.write((char*)&spawnTimerMax, sizeof(float));
    file.close();
}

void GAME::loadGame() {
    std::ifstream file2;
    file2.open("Game.txt", std::ios::in);
    if (!file2) {
        std::cout << "Unable to open save game!" << std::endl;
        return;
    }
    std::cout << "Open save game successfuly!" << std::endl;
    if (file2.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "Game file is empty, let's play new game!!" << std::endl;
        return;
    }
    file2.read((char*)&this->view, sizeof(sf::View));
    file2.read((char*)&this->isPause, sizeof(bool));
    file2.read((char*)&this->level, sizeof(unsigned));
    file2.read((char*)&this->scene, sizeof(unsigned));
    file2.read((char*)&this->deltaTime, sizeof(float));
    file2.read((char*)&this->clock, sizeof(sf::Clock));
    SPACESHIP player;
    file2.read((char*)&player, sizeof(SPACESHIP));
    this->setSPACESHIP(player);
    this->player->initAfterLoad();
    /*GUI gui;
    file2.read((char*)&gui, sizeof(GUI));
    this->setGUI(gui);*/
    file2.read((char*)&this->menu, sizeof(MENU));
    file2.read((char*)&this->spawnTimer, sizeof(float));
    file2.read((char*)&this->spawnTimerMax, sizeof(float));
    file2.close();
}

GAME& GAME::operator=(GAME other) {
    std::swap(window, other.window);
    /*std::swap()*/
    return *this;
}

void GAME::setSPACESHIP(SPACESHIP player) {
    swap(this->player, &player);
}

void GAME::setGUI(GUI gui) {
    swap(this->gui, &gui);
}

void GAME::setSpawnTimer(float spawnTimer) {
    this->spawnTimer = spawnTimer;
}

void GAME::setSpawnTimerMax(float spawnTimerMax) {
    this->spawnTimerMax = spawnTimerMax;
}

void GAME::setClocK(sf::Clock clock) {
    this->clock = clock;
}

void GAME::setDeltaTime(float deltaTime) {
    this->deltaTime = deltaTime;
}

void GAME::setLevel(unsigned level) {
    this->level = level;
}

void GAME::setScene(unsigned scene) {
    this->scene = scene;
}

void setTextures(std::map<std::string, sf::Texture*> other) {
}

void GAME::setWindow(sf::RenderWindow window) {
    swap(this->window, &window);
}

void GAME::setView(sf::View view) {
    this->view = view;
}

void GAME::setIsPause(bool isPause) {
    this->isPause = isPause;
}

template <class T>void swap(T* a, T*b) {
    T* c = a;
    a = b;
    b = c;
}