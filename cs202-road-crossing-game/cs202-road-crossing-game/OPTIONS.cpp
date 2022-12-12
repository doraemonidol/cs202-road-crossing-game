#include "OPTIONS.h"
#include "UTILS.h"
#include "GAME.h"
#include "main.h"

OPTIONS::OPTIONS() {
    //soundController = new SoundManager("Sound/btn-switch.wav");
}

OPTIONS::OPTIONS(std::vector<std::string> but, std::string fon, int charSize, std::string activeTexture, sf::Color textColor[], int index)
{
    selectedItemIndex = 0;
    for (int i = 0; i < but.size(); i++) {
        this->addButton(but[i], fon, charSize, activeTexture, textColor, index + i + 1);
    }
    this->button[0]->onHover();
}

OPTIONS::~OPTIONS()
{
}

void OPTIONS::init()
{
    button[selectedItemIndex]->onHover();
    //soundController = new SoundManager();
}

void OPTIONS::addButton(std::string t, std::string fon, int charSize, std::string activeTexture, sf::Color textColor[], int index)
{
    button.push_back(new BUTTON(t, fon, charSize, activeTexture, textColor, index));
}

void OPTIONS::draw(sf::RenderWindow* window)
{
    for (int i = 0; i < button.size(); i++) {
        this->button[i]->drawTo(window);
    }
}

void OPTIONS::MoveUp()
{
    if (selectedItemIndex - 1 >= 0) {
        button[selectedItemIndex]->onDefault();
        selectedItemIndex--;
        button[selectedItemIndex]->onHover();
    }
}

void OPTIONS::MoveDown()
{
    if (selectedItemIndex + 1 < button.size()) {
        button[selectedItemIndex]->onDefault();
        selectedItemIndex++;
        button[selectedItemIndex]->onHover();
    }
}

int OPTIONS::update(sf::RenderWindow* window, sf::Event e, GAME* gm)
{
    if (e.type == sf::Event::KeyPressed) {
        switch (e.key.code) {
        case sf::Keyboard::Up:
            switchSFX(gm);
            MoveUp();
            break;
        case sf::Keyboard::Down:
            switchSFX(gm);
            MoveDown();
            break;
        case sf::Keyboard::Enter:
            pressSFX(gm);
            return this->button[selectedItemIndex]->getIndex();
            break;
        default:
            break;
        }
    } 
    if (e.type == sf::Event::MouseMoved || e.type == sf::Event::MouseButtonPressed) {
        for (int i = 0; i < button.size(); i++) {
            int state = this->button[i]->update(window, e);
            switch (state) {
            case ACTIVE:
                pressSFX(gm);
                return this->button[i]->getIndex();
            case HOVER:
                if (i != selectedItemIndex) {
                    switchSFX(gm);
                    button[selectedItemIndex]->onDefault();
                    selectedItemIndex = i;
                }
                break;
            default:
                break;
            }
        }
    }
    return -1;
}

void OPTIONS::unpdateButtonDisplacement(sf::Vector2f pos)
{
    for (int i = 0; i < button.size(); i++) {
        this->button[i]->updateDisplacement(pos);
    }
}

void OPTIONS::movePos(sf::Vector2f pos) {
    this->pos = pos;
    for (int i = 0; i < button.size(); i++) {
        this->button[i]->movePosition(pos);
    }
}

void OPTIONS::alignButtons(int type) {
    switch (type) {
    case ALIGN_CENTER:
        sf::Vector2f pos(SCREEN_WIDTH / 2, 2);
    }
}
void OPTIONS::tidyButtons(float padding)
{
    float sumY = 0;
    for (int i = 0; i < button.size(); i++) {
        sumY += button[i]->getSize().height;
    }
    float y0 = (SCREEN_HEIGHT - sumY - padding * button.size()) / 2;
    sumY = y0;

    for (int i = 0; i < button.size(); i++) {
        button[i]->setPosition(sf::Vector2f(SCREEN_WIDTH / 2, sumY));
        sumY += button[i]->getSize().height + padding;
    }
}

void OPTIONS::pressSFX(GAME* gm)
{
    gm->playSound(PRESS_SFX);
}

void OPTIONS::switchSFX(GAME* gm)
{
    gm->playSound(SWITCH_SFX);
}

void OPTIONS::attachSoundController(SoundManager* sm)
{
    soundController = sm;
}
