#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

#include "SoundEffect.hpp"

#include <SFML/Audio.hpp>

constexpr int maxSounds = 100;

class SoundManager {
public:
    SoundManager();
    SoundManager(std::string name);
    SoundManager(SoundManager const& src);
    ~SoundManager(void);

    SoundManager& operator=(SoundManager const& rhs);
    std::string toString(void) const;
    void playSound(std::string name);
    void playEffect(std::string name);
    void update(void);

    static SoundManager* instance;
    void switchMute();

    void clearQueue();
    void saveGame(std::string fileName);

private:
    std::priority_queue<std::shared_ptr<SoundEffect>> _sounds;
    sf::Music _music;
    std::string _musicName;
    bool isMute;
};

std::ostream& operator<<(std::ostream& o, SoundManager const& rhs);

#endif