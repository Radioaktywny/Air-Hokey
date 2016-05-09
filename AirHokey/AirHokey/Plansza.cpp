#include "Plansza.h"
#include "SFML/Graphics.hpp"


Plansza::Plansza()
{
	this->color = sf::Color(50, 205, 255);
	this->wymiary = sf::Vector2f(1600, 900);
	initBoisko();	
}
Plansza::Plansza(sf::Vector2f wymiary, sf::Color color)
{
	this->wymiary = wymiary;
	this->color = color;
	initBoisko();	
}
void Plansza::initBoisko()
{
	boisko.setFillColor(color);
	boisko.setPosition(50, 50);
	boisko.setSize(wymiary);
}
void Plansza::rysuj(sf::RenderWindow* window)
{
	window->draw(boisko);	
}
bool Plansza::czyWplanszy(sf::CircleShape* object)
{
	return boisko.getGlobalBounds().intersects(object->getGlobalBounds());
}
Plansza::~Plansza()
{

}
