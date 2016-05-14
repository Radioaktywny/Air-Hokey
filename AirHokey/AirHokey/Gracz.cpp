#include "Gracz.h"
#include "SFML/Graphics.hpp"
Gracz::Gracz()
{
	this->krazek.setFillColor(sf::Color::Blue);
	this->krazek.setRadius(50);
	this->krazek.setPosition(100, 100);
}

Gracz::~Gracz()
{
}

void Gracz::move(sf::Vector2f dir)
{
	this->kierunek = dir - krazek.getPosition();
	this->kierunek=sf::Vector2f(kierunek.x-krazek.getRadius(),kierunek.y-krazek.getRadius());
	krazek.move(kierunek.x , kierunek.y);
}

void Gracz::rysuj(sf::RenderWindow * window)
{
	window->draw(this->krazek);
}

sf::Vector2f Gracz::getKierunek()
{
	return kierunek;
}

sf::CircleShape* Gracz::getShape()
{
	return &krazek;
}