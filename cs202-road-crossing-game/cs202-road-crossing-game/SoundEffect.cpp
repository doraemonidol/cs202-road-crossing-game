#include "SoundEffect.hpp"
#pragma warning(disable : 4996)

SoundEffect::SoundEffect(std::string name)
{
	time(&_timer);
	_name = name;
	if (!_buffer.loadFromFile(name))
		throw std::runtime_error("sfml error : loadFromfile.");
	_sound.setBuffer(_buffer);
	_timer += static_cast<int>(_buffer.getDuration().asSeconds()) + 1;
	_sound.play();
}

SoundEffect::~SoundEffect(void)
{
}

void			SoundEffect::handleQueue(std::priority_queue<std::shared_ptr<SoundEffect> > &sounds)
{
	time_t			t;

	time(&t);
	while (sounds.size() && sounds.top()->_timer <= t)
		sounds.pop();
}


std::string		SoundEffect::toString(void) const
{
	std::stringstream	ss;
	tm					now = *localtime(&_timer);
	const char			fmt[] = "[ %X ] > ";
	char				tmstp[80]{0};

	strftime(tmstp, sizeof(tmstp) - 1, fmt, &now);

	ss << _name << " will end at " << tmstp;
	return (ss.str());
}

bool			operator<(const std::shared_ptr<SoundEffect> a, const std::shared_ptr<SoundEffect> b)
{
	return (*a < *b);
}

bool			SoundEffect::operator<(SoundEffect const & ref) const
{
	return ((_timer > ref._timer));
}


std::ostream	&operator<<(std::ostream & o, SoundEffect const & rhs)
{
	o << rhs.toString();
	return (o);
}
