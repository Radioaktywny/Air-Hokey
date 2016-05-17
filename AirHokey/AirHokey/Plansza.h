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
	sf::Vector2f getSrodek();
	private:
	sf::Vector2f wymiary;
	sf::CircleShape polowaKolo;
	sf::RectangleShape liniaSrodkowa;	
	sf::Color color;
	sf::RectangleShape boisko;
	sf::RectangleShape linieboczne[4];
	sf::RectangleShape bramki[2];
	void initBoisko();
};

