#include <string>
#pragma once

class GameOver
{
public:
	GameOver();
	~GameOver();
	std::string run(sf::RenderWindow * window, sf::Font * font , std::string * wygral, std::string type);
};

