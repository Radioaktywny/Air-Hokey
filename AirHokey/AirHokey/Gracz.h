#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Gracz
{
public:
	Gracz();
	Gracz(int numer);
	~Gracz();
	void move(sf::Vector2f dir);
	void rysuj(sf::RenderWindow * window);
	sf::Vector2f getKierunek();
	sf::CircleShape getShape();

private:
	sf::CircleShape krazek;
	sf::Vector2f kierunek;
};