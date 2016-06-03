#include "Gracz.h"
#include "SFML/Graphics.hpp"
#include <iostream>
Gracz::Gracz()
{
	this->krazek.setFillColor(sf::Color::Blue);
	this->krazek.setRadius(40);
	//this->krazek.setPosition(100, 100);
}
Gracz::Gracz(sf::Color kolor)
{
	this->krazek.setFillColor(kolor);
	this->krazek.setRadius(40);
	//this->krazek.setPosition(100, 100);
}

Gracz::~Gracz()
{
}

void Gracz::move(sf::Vector2f dir)
{
	this->kierunek = dir - krazek.getPosition();
	this->kierunek=sf::Vector2f(kierunek.x-krazek.getRadius(),kierunek.y-krazek.getRadius());
	float predkosc = sqrtf((kierunek.x*kierunek.x) +( kierunek.y*kierunek.y));
	if (predkosc > 6)
	{
		kierunek.x = 6*kierunek.x/predkosc;
		kierunek.y = 6 *kierunek.y / predkosc;
	}
	krazek.move(kierunek.x , kierunek.y);
}

void Gracz::rysuj(sf::RenderWindow * window)
{
	window->draw(this->krazek);
}

sf::Vector2f Gracz::getKierunek()
{
	return this->kierunek;
}

sf::CircleShape Gracz::getShape()
{
	return this->krazek;
}

void Gracz::setPosition(int x, int y)
{
	this->krazek.setPosition(x, y);
}

