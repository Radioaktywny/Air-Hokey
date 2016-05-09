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
	krazek.move((dir.x - krazek.getPosition().x) - krazek.getRadius(), (dir.y - krazek.getPosition().y) - krazek.getRadius());
}

void Gracz::rysuj(sf::RenderWindow * window)
{
	window->draw(this->krazek);
}
