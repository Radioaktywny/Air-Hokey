#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#pragma once

class Connection
{
public:
	Connection();
	~Connection();
	void isServer(sf::CircleShape *gracz1, sf::CircleShape *gracz2, sf::CircleShape *krazek, sf::RenderWindow *window);
	void isClient(sf::CircleShape *gracz1, sf::CircleShape *gracz2, sf::CircleShape *krazek, sf::RenderWindow * window);
};
