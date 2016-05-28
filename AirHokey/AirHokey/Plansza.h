#pragma once
#include<SFML/Graphics.hpp>
#include "Krazek.h"

class Plansza
{
public:
	sf::Vector2f bramka;
	Plansza();
	Plansza(sf::Vector2f wymiary,sf::Color color);
	~Plansza();
	void rysuj(sf::RenderWindow* window);
	short czyWplanszy(Krazek* object);
	sf::Vector2f getSrodek();
	sf::RectangleShape linieboczne[6];
private:
	sf::Vector2f wymiary;
	sf::CircleShape polowaKolo;
	sf::RectangleShape liniaSrodkowa;	
	sf::Color color;
	sf::RectangleShape boisko;
	sf::RectangleShape bramki[2];
	sf::CircleShape slupki[4];
	void initBoisko();
};

