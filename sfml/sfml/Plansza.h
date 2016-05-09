#pragma once
#include<SFML/Graphics.hpp>
class Plansza
{
public:
	Plansza();
	Plansza(sf::Vector2f wymiary,sf::Color color);
	~Plansza();
	void rysuj(sf::RenderWindow* window);
private:
	sf::CircleShape polowaKolo;
	sf::RectangleShape liniaSrodkowa;
	sf::Vector2f wymiary;
	sf::Color color;
	sf::RectangleShape boisko;
	void initBoisko();
};

