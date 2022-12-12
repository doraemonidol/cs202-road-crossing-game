#ifndef SOUNDEFFECT_HPP
# define SOUNDEFFECT_HPP

# include <iostream>
# include <sstream>
# include <string>
# include <exception>
# include <queue>

# include <SFML/Audio.hpp>

	class SoundEffect
	{
		public:

			SoundEffect(void);
			SoundEffect(std::string);
			SoundEffect(SoundEffect const &src);
			~SoundEffect(void);
		
			SoundEffect		&operator=(SoundEffect const &rhs);
			bool			operator<(SoundEffect const & ref) const;
			std::string		toString(void) const;

			static void		handleQueue(std::priority_queue<std::shared_ptr<SoundEffect> > &sounds);
		
		private:
			sf::SoundBuffer	_buffer;
			sf::Sound		_sound;
			time_t			_timer;
			std::string		_name;
	};

	std::ostream	&operator<<(std::ostream &o, SoundEffect const &rhs);

#endif