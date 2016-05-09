#pragma once
#include<SFML/Graphics.hpp>
class Gracz
{
public:
	Gracz();
	~Gracz();
	void move(sf::Vector2f dir);
	void rysuj(sf::RenderWindow * window);
	sf::CircleShape* getShape();

private:
	sf::CircleShape krazek;
};

