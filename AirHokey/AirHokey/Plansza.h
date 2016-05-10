#pragma once
#include<SFML/Graphics.hpp>
#include "Krazek.h"

class Plansza
{
public:
	Plansza();
	Plansza(sf::Vector2f wymiary,sf::Color color);
	~Plansza();
	void rysuj(sf::RenderWindow* window);
	void czyWplanszy(Krazek* object);
	private:
	sf::CircleShape polowaKolo;
	sf::RectangleShape liniaSrodkowa;
	sf::Vector2f wymiary;
	sf::Color color;
	sf::RectangleShape boisko;
	sf::RectangleShape linieboczne[4];
	void initBoisko();
};

