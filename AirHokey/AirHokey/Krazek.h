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
	void rysuj(sf::RenderWindow * window);
	sf::Vector2f getPredkosc();
	sf::FloatRect zwroc();
private:
	sf::Vector2f kierunek;
	float przyspieszenie;
	sf::Vector2f start;
	sf::Color color;
	sf::CircleShape krazek;
	float wielkosc;
	void init();
	void move();
};

