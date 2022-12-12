#include "SoundManager.hpp"

SoundManager	*SoundManager::instance = NULL;


SoundManager::SoundManager()
{
	if (!instance)
		instance = this;
	else
		throw std::runtime_error("SoundManager is unique.");
	_music.setLoop(true);
	_musicName = "";
}

SoundManager::SoundManager(std::string name)
{
	if (!instance)
		instance = this;
	else
		throw std::runtime_error("SoundManager is unique.");
	_music.setLoop(true);
	playSound(name);
}


SoundManager::~SoundManager(void)
{
}

void			SoundManager::playSound(std::string name)
{
	if (!_music.openFromFile(name))
		throw std::runtime_error("sfml error : openFromFile.");
	_music.play();
	_musicName = name;
}

void			SoundManager::playEffect(std::string name)
{
	if (_sounds.size() > maxSounds)
		return ;
	_sounds.push(std::shared_ptr<SoundEffect>(new SoundEffect(name)));
}

void			SoundManager::update(void)
{
	SoundEffect::handleQueue(_sounds);
}

std::string		SoundManager::toString(void) const
{
	std::stringstream	ss;

	ss << "BackGround music: " << _musicName << std::endl;
	ss << "Total SoundEffect in memory : " << _sounds.size() << std::endl;
	if (_sounds.size())
		ss << *(_sounds.top()) << " will end soon." << std::endl;
	return (ss.str());
}

std::ostream	&operator<<(std::ostream & o, SoundManager const & rhs)
{
	o << rhs.toString();
	return (o);
}
