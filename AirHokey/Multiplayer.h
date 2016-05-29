#include <SFML/Graphics.hpp>
#pragma once
class Multiplayer
{
public:
	Multiplayer();
	~Multiplayer();
	std::string run(sf::RenderWindow * window, sf::Font * font, std::string * wygral, std::string state);
};

