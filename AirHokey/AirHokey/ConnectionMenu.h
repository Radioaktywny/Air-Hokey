#include <SFML/Graphics.hpp>
#pragma once
class ConnectionMenu
{
public:
	ConnectionMenu();
	~ConnectionMenu();
	std::string ConnectionMenu::run(sf::RenderWindow *window, sf::Font * font);
};

