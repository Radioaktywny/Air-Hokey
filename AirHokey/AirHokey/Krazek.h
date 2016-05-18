#pragma once
#include "SFML/Graphics.hpp"
class Krazek
{
public:
	Krazek();
	Krazek(sf::Color color, sf::Vector2f start);
	~Krazek();
	void setPredkosc(sf::Vector2f kierunek);
	void rysuj(sf::RenderWindow * window);
	sf::Vector2f getPredkosc();
	void gol(sf::Vector2f srodek);
	sf::CircleShape zwroc();	
	void move();
private:
	sf::Vector2f kierunek;
	float maxpredkosc;
	sf::Vector2f start;
	sf::Color color;
	sf::CircleShape krazek;
	float wielkosc;
	void init();	
};

