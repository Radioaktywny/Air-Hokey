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
<<<<<<< HEAD
	sf::RectangleShape linieboczne[4];
=======
>>>>>>> origin/Marcin
	private:
	sf::Vector2f wymiary;
	sf::CircleShape polowaKolo;
	sf::RectangleShape liniaSrodkowa;	
	sf::Color color;
	sf::RectangleShape boisko;
<<<<<<< HEAD
=======
	sf::RectangleShape linieboczne[4];
>>>>>>> origin/Marcin
	sf::RectangleShape bramki[2];
	void initBoisko();
};

