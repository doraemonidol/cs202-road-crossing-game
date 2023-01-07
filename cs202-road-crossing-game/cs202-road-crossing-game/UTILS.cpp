
#include "main.h"

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
    isPlayingAnim = false;
}

BUTTON::BUTTON(std::string hoverT, std::string activeT, std::string defaultT)
{
    for (int i = 0; i < btnStateCnt; i++)
        bgColor[i] = sf::Color::Transparent;
    setTexture(hoverT, activeT, defaultT);
    button.setSize(sf::Vector2f(texture[DEFAULT].getSize()));
    type = 3;
    state = DEFAULT;
    isPlayingAnim = false;
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
    isPlayingAnim = false;
}

BUTTON::BUTTON(std::string t, std::string fon, int charSize, std::string activeTexture, sf::Color textColor[btnStateCnt], int index)
{
    this->index = index;
    for (int i = 0; i < btnStateCnt; i++)
        bgColor[i] = sf::Color::Transparent;
    for (int i = 0; i < btnStateCnt; i++) {
        this->textColor[i] = textColor[i];
    }

    text.setString(t);
    text.setColor(textColor[DEFAULT]);
    text.setCharacterSize(charSize);
    this->setFont(fon);

    sf::Vector2f size = sf::Vector2f(text.getGlobalBounds().width + 80.f, text.getGlobalBounds().height + 20.f);
    button.setSize(size);
    button.setFillColor(bgColor[DEFAULT]);
    
    //button.setOutlineColor(sf::Color::White);
    //button.setOutlineThickness(2);
    if (!this->texture[ACTIVE].loadFromFile("Textures/" + activeTexture)) {
        std::cout << "ERROR::BUTTON::BUTTON5::ACTIVE::Could not load texture file.\n";
    }
    activeSprite.setTexture(texture[ACTIVE]);
    button.setOrigin(button.getGlobalBounds().width / 2, button.getGlobalBounds().height / 2);
    text.setOrigin(button.getGlobalBounds().width / 2, button.getGlobalBounds().height / 2);
    //activeSprite.setOrigin(button.getGlobalBounds().width / 2, button.getGlobalBounds().height / 2);
    type = 5;
    state = DEFAULT;
    pos = sf::Vector2f(0, 0);
    isPlayingAnim = false;
}

BUTTON::BUTTON(std::string switchAnim, sf::Vector2u imgCnt, float switchTime, sf::Vector2f pos, int index)
{
    this->index = index;
    if (!this->texture[DEFAULT].loadFromFile("Textures/" + switchAnim)) {
        std::cout << "ERROR::BUTTON::BUTTON6::DEFAULT::Could not load texture file.\n";
    }
    this->switchAnim.initAnim(&(this->texture[DEFAULT]), imgCnt, switchTime);
    
    activeSprite.setTexture(texture[DEFAULT]);
    this->activeSprite.setTextureRect(this->switchAnim.uvRect);

    // button.setOutlineColor(sf::Color::White);
    // button.setOutlineThickness(2);
    button.setSize(sf::Vector2f(this->switchAnim.uvRect.width, this->switchAnim.uvRect.height));
    button.setOrigin(button.getGlobalBounds().width / 2, button.getGlobalBounds().height / 2);
    button.setFillColor(sf::Color::Transparent);
    button.setPosition(pos);

    // text.setOrigin(button.getGlobalBounds().width / 2, button.getGlobalBounds().height / 2);
    activeSprite.setOrigin(button.getGlobalBounds().width / 2, button.getGlobalBounds().height / 2);
    activeSprite.setPosition(pos);
    
    type = 6;
    state = DEFAULT;
    this->pos = sf::Vector2f(0, 0);
    isPlayingAnim = false;
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
    //activeSprite.setPosition(xPos, yPos);
}

void BUTTON::movePosition(sf::Vector2f pos)
{
    button.setPosition(button.getPosition().x + pos.x, button.getPosition().y + pos.y);

    float xPos = (button.getPosition().x + button.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2);
    float yPos = (button.getPosition().y + button.getGlobalBounds().height / 2) - (text.getGlobalBounds().height / 2);
    text.setPosition(xPos, yPos);
}

void BUTTON::movePosition2(sf::Vector2f pos)
{
    button.setPosition(button.getPosition().x + pos.x - this->pos.x, button.getPosition().y + pos.y - this->pos.y);

    float xPos = (button.getPosition().x + button.getGlobalBounds().width / 2) - (text.getGlobalBounds().width / 2);
    float yPos = (button.getPosition().y + button.getGlobalBounds().height / 2) - (text.getGlobalBounds().height / 2);
    text.setPosition(xPos, yPos);

    activeSprite.setPosition(button.getPosition());

    this->pos = pos;
}
void BUTTON::updateDisplacement(sf::Vector2f pos)
{
    this->pos = pos;
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
            case 6:
                window->draw(activeSprite);
                break;
            }
            break;
        case HOVER:
            switch (type) {
            case 5:
                window->draw(activeSprite);
                break;
            case 6:
                window->draw(activeSprite);
                break;
            }
            break;
        case DEFAULT:
            switch (type) {
            case 5:
                break;
            case 6:
                window->draw(activeSprite);
                break;
            }
            break;
    }
}

bool BUTTON::isMouseOver(sf::RenderWindow* window)
{
    float mouseX = sf::Mouse::getPosition(*window).x + pos.x;
    float mouseY = sf::Mouse::getPosition(*window).y + pos.y;
    //std::cout << mouseX << " " << mouseY << "\n";

    if (mouseX < button.getPosition().x + button.getGlobalBounds().width / 2 && mouseX > button.getPosition().x - button.getGlobalBounds().width / 2 && 
        mouseY < button.getPosition().y + button.getGlobalBounds().height / 2 && mouseY > button.getPosition().y - button.getGlobalBounds().height / 2) {
        return true;
    }
    return false;
}

void BUTTON::onDefault()
{
    switch (type) {
    case 5: 
        text.setColor(textColor[DEFAULT]);

        // this->activeSprite.setPosition(sf::Vector2f(button.getPosition()));
        //  this->playerHp[i].setScale(2.f, 2.f);
        break;

    case 6:
        break;
    }
    state = DEFAULT;
    
}

void BUTTON::onClick() {
    switch (type) {
    case 5: 
        text.setColor(textColor[ACTIVE]);

        this->activeSprite.setPosition(sf::Vector2f(button.getPosition().x - button.getGlobalBounds().width / 2, button.getPosition().y - activeSprite.getGlobalBounds().height / 2));
      //  this->playerHp[i].setScale(2.f, 2.f);
        break;
    case 6:
        isPlayingAnim = true;
        break;
    }
    state = ACTIVE;
}

void BUTTON::onHover() {
    switch (type) {
    case 5: 
        text.setColor(textColor[ACTIVE]);

        this->activeSprite.setPosition(sf::Vector2f(button.getPosition().x - button.getGlobalBounds().width / 2, button.getPosition().y - activeSprite.getGlobalBounds().height / 2));
        //  this->playerHp[i].setScale(2.f, 2.f);
        break;
    case 6:
        break;
    }
    state = HOVER;
}

int BUTTON::update(sf::RenderWindow* window, sf::Event e, float deltaTime)
{
    if (isPlayingAnim)
        return DEFAULT;

    if (isMouseOver(window)) {
        switch (type) {
        case 6:
            if (e.type == sf::Event::MouseButtonPressed) {
                onClick();
            }
            break;
        default:
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
    }
    return DEFAULT;
}
int BUTTON::updateAnim(float deltaTime)
{
    if (isPlayingAnim) {
        switch (type) {
        case 6:
            //std::cout << "\n switch anim " << switchAnim.getCurImgCnt().y << " ";
            isPlayingAnim = !switchAnim.Update(switchAnim.getCurImgCnt().y, deltaTime, true);
            this->activeSprite.setTextureRect(this->switchAnim.uvRect);
            if (!isPlayingAnim) {
                switchAnim.setCurImg(sf::Vector2u(0, (switchAnim.getCurImgCnt().y + 1) % 2));
                this->activeSprite.setTextureRect(this->switchAnim.uvRect);
                return ACTIVE;
            }
            break;
        default:
            break;
        }
        return DEFAULT;
    }
}
sf::FloatRect BUTTON::getSize() {
    return button.getGlobalBounds();
}
int BUTTON::getIndex() {
    return index;
}

void BUTTON::changeText(std::string newText)
{
    text.setString(newText);
}

std::string BUTTON::getText()
{
    return text.getString().toAnsiString();
}

void BUTTON::saveGame(std::string fileName) {
    std::ofstream file;
    file.open(fileName, std::ios::app);
    file.write((char*)&type, sizeof(int));
    file.write((char*)&index, sizeof(int));
    file.write((char*)state, sizeof(state));
    file.write((char*)&isPlayingAnim, sizeof(bool));
    file.write((char*)&toReturn, sizeof(int));
    file.close();
}

Textbox::Textbox(sf::RenderWindow& windowToUse, sf::Font& fontToUse) : window(windowToUse), font(fontToUse) {
    text = sf::Text("", font);
    background.setFillColor(sf::Color::White);
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(2);
    text.setColor(sf::Color::Black);
    x = window.getSize().x;
    y = window.getSize().y;
    x = x / 2 - 400 / 2;
    y = y / 2 - 50 / 2;
    text.setPosition(x + 10, y + 13);
    text.setCharacterSize(25);
    background.setPosition(x, y);
    background.setSize(sf::Vector2f(400, 50));
    title = sf::Text("Please input your file", font);
    title.setCharacterSize(30);
    title.setPosition(x - 123, y - 50);
    title.setColor(sf::Color::White);
}

void Textbox::draw() {
    window.draw(background);
    window.draw(title);
    window.draw(text);
}


void Textbox::setString(std::string newString) {
    string = newString;
    text.setString(string);
}

std::string Textbox::getString() {
    return string;
}

bool Textbox::pollEvent(sf::Event event) {

    if (event.type == sf::Event::TextEntered) {
        return enterText(event.text.unicode);
    }
           
    return false;
}

void Textbox::setFocus(bool newFocus) {
    isFocused = newFocus;
}

bool Textbox::enterText(sf::Uint32 unicode) {
    if (unicode == 8)
        string = string.substr(0, string.length() - 1); // delete key
    else if (unicode == 13) {
        return true; // return key
    }  
    else {
        string += (char)unicode;
    }
    if (string.length() > 15) {
        string = string.substr(1, string.length());
    }
    text.setString(string);
    std::cout << "Set string" << std::endl;
    return false;
}