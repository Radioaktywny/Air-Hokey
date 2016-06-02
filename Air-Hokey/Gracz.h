#pragma once
#include<SFML/Graphics.hpp>

class Gracz
{
public:
	Gracz();
	Gracz(sf::Color kolor);
	~Gracz();
	void move(sf::Vector2f dir);
	void rysuj(sf::RenderWindow * window);
	sf::Vector2f getKierunek();
	sf::CircleShape getShape();
	void setPosition(int x, int y);

private:
	sf::CircleShape krazek;
	sf::Vector2f kierunek;

};

