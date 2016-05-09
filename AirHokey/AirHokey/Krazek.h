#pragma once
#include "SFML/Graphics.hpp"

class Krazek
{
public:
	Krazek();
	Krazek(sf::Color color, sf::Vector2f start);
	~Krazek();
	void setPredkosc(sf::Vector2f kierunek);
	void setPrzyspieszenie(float przyspieszenie);
	void setPredkosc(float predkosc);
	void rysuj(sf::RenderWindow * window);
private:
	sf::Vector2f kierunek;
	float predkosc;
	float przyspieszenie;
	sf::Vector2f start;
	sf::Color color;
	sf::CircleShape krazek;
	float wielkosc;
	void init();
	void move();
};

