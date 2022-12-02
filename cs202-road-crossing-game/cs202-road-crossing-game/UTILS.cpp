#include "UTILS.h"

BUTTON::BUTTON(std::string t, int charSize, sf::Vector2f size, sf::Color bgColor, sf::Color textColor)
{
    for (int i = 0; i < btnStateCnt; i++)
        this->bgColor[i] = sf::Color::Transparent;
    text.setString(t);
    text.setColor(textColor);
    text.setCharacterSize(charSize);

    button.setSize(size);
    button.setFillColor(bgColor);
    type = 2;
    state = DEFAULT;
}

BUTTON::BUTTON(std::string hoverT, std::string activeT, std::string defaultT)
{
    for (int i = 0; i < btnStateCnt; i++)
        bgColor[i] = sf::Color::Transparent;
    setTexture(hoverT, activeT, defaultT);
    button.setSize(sf::Vector2f(texture[DEFAULT].getSize()));
    type = 3;
    state = DEFAULT;
}

BUTTON::BUTTON(std::string t, std::string fon, int charSize, sf::Vector2f size, sf::Color bgColor[btnStateCnt], sf::Color textColor[btnStateCnt])
{
    for (int i = 0; i < btnStateCnt; i++)
        bgColor[i] = sf::Color::Transparent;
    for (int i = 0; i < btnStateCnt; i++) {
        this->bgColor[i] = bgColor[i];
        this->textColor[i] = textColor[i];
    }

    text.setString(t);
    text.setColor(textColor[DEFAULT]);
    text.setCharacterSize(charSize);
    this->setFont(fon);

    button.setSize(size);
    button.setFillColor(bgColor[DEFAULT]);
    type = 4;
    state = DEFAULT;
}

BUTTON::BUTTON(std::string t, std::string fon, int charSize, sf::Vector2f size, std::string activeTexture, sf::Color textColor[btnStateCnt])
{
    for (int i = 0; i < btnStateCnt; i++)
        bgColor[i] = sf::Color::Transparent;
    for (int i = 0; i < btnStateCnt; i++) {
        this->textColor[i] = textColor[i];
    }

    text.setString(t);
    text.setColor(textColor[DEFAULT]);
    text.setCharacterSize(charSize);
    button.setSize(size);
    this->setFont(fon);

    button.setFillColor(bgColor[DEFAULT]);
    //button.setOutlineColor(sf::Color::White);
    //button.setOutlineThickness(2);
    if (!this->texture[ACTIVE].loadFromFile("Textures/" + activeTexture)) {
        std::cout << "ERROR::BUTTON::BUTTON5::ACTIVE::Could not load texture file.\n";
    }
    activeSprite.setTexture(texture[ACTIVE]);
    type = 5;
    state = DEFAULT;
}

void BUTTON::setFont(std::string fon)
{
    font.loadFromFile("Fonts/" + fon);
    text.setFont(font);
}

void BUTTON::setBackColor(sf::Color color)
{
    button.setFillColor(color);
}

void BUTTON::setTextColor(sf::Color color)
{
    text.setColor(color);
}

void BUTTON::setPosition(sf::Vector2f pos)
{
    button.setPosition(pos);
    //std::string name = text.getString();
    //std::cout << name << std::endl;

    float xPos = (pos.x + button.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2);
    float yPos = (pos.y + button.getGlobalBounds().height / 2) - (text.getGlobalBounds().height / 2);
    text.setPosition(xPos, yPos);
}

void BUTTON::setTexture(std::string hoverT, std::string activeT, std::string defaultT)
{
    //Load a texture from file
    if (!this->texture[HOVER].loadFromFile("Textures/" + hoverT)) {
        std::cout << "ERROR::BUTTON::SETTEXTURE::HOVER::Could not load texture file.\n";
    }
    if (!this->texture[ACTIVE].loadFromFile("Textures/" + activeT)) {
        std::cout << "ERROR::BUTTON::SETTEXTURE::ACTIVE::Could not load text*ure file.\n";
    }
    if (!this->texture[DEFAULT].loadFromFile("Textures/" + defaultT)) {
        std::cout << "ERROR::BUTTON::SETTEXTURE::DEFAULT::Could not load texture file.\n";
    }
}

void BUTTON::drawTo(sf::RenderWindow* window)
{
    window->draw(button);
    window->draw(text);
    switch (state) {
        case ACTIVE: 
            switch (type) {
            case 5: 
                window->draw(activeSprite);
                break;
                
            }
            break;
        case HOVER:
            switch (type) {
            case 5:
                window->draw(activeSprite);
                break;
            }
            break;
        
    }
}

bool BUTTON::isMouseOver(sf::RenderWindow* window)
{
    float mouseX = sf::Mouse::getPosition(*window).x;
    float mouseY = sf::Mouse::getPosition(*window).y;

    float btnPosX = button.getPosition().x;
    float btnPosY = button.getPosition().y;

    float btnPosWidth = button.getPosition().x + button.getGlobalBounds().width;
    float btnPosHeight = button.getPosition().y + button.getGlobalBounds().height;

    if (mouseX < btnPosWidth && mouseX > btnPosX && mouseY < btnPosHeight && mouseY > btnPosY) {
        return true;
    }
    return false;
}

void BUTTON::onDefault()
{
    switch (type) {
    case 5: {
        text.setColor(textColor[DEFAULT]);

        // this->activeSprite.setPosition(sf::Vector2f(button.getPosition()));
        //  this->playerHp[i].setScale(2.f, 2.f);
        break;
    }
    }
    state = DEFAULT;
    
}

void BUTTON::onClick() {
    switch (type) {
    case 5: {
        text.setColor(textColor[ACTIVE]);

        this->activeSprite.setPosition(sf::Vector2f(button.getPosition().x, button.getPosition().y + (button.getGlobalBounds().height - activeSprite.getGlobalBounds().height) / 2));
      //  this->playerHp[i].setScale(2.f, 2.f);
        break;
    }
    }
    state = ACTIVE;
}

void BUTTON::onHover() {
    switch (type) {
    case 5: {
        text.setColor(textColor[ACTIVE]);

        this->activeSprite.setPosition(sf::Vector2f(button.getPosition().x, button.getPosition().y + (button.getGlobalBounds().height - activeSprite.getGlobalBounds().height) / 2));
        //  this->playerHp[i].setScale(2.f, 2.f);
        break;
    }
    }
    state = HOVER;
}

int BUTTON::update(sf::RenderWindow* window, sf::Event e)
{
    if (isMouseOver(window)) {
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Enter) {
            onClick();
            return ACTIVE;
        } else if (e.type == sf::Event::MouseButtonPressed) {
            onClick();
            return ACTIVE;
        }
        onHover();
        return HOVER;
    }
    return DEFAULT;
}