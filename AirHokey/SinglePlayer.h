#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class SinglePlayer
{
public:
	SinglePlayer();
	~SinglePlayer();
	std::string run(sf::RenderWindow * window, sf::Font * font , std::string * wygral);

private:
	
};

