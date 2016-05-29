#include "Gracz.h"
#include "SFML/Graphics.hpp"
Gracz::Gracz()
{
	this->krazek.setFillColor(sf::Color::Blue);
	this->krazek.setRadius(40);
	this->krazek.setPosition(100, 100);
}

Gracz::~Gracz()
{
}

void Gracz::move(sf::Vector2f dir)
{
	this->kierunek = dir - krazek.getPosition();
	this->kierunek=sf::Vector2f(kierunek.x-krazek.getRadius(),kierunek.y-krazek.getRadius());
	float predkosc = sqrtf((kierunek.x*kierunek.x) +( kierunek.y*kierunek.y));
	if (predkosc > 0.3)
	{
		kierunek.x = 0.3*kierunek.x/predkosc;
		kierunek.y = 0.3 *kierunek.y / predkosc;
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
