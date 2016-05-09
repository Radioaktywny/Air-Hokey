#include "Krazek.h"
#include "SFML/Graphics.hpp"



Krazek::Krazek()
{
	this->color = sf::Color(sf::Color::Green);
	this->start = sf::Vector2f(500, 500);
	init();
}
Krazek::Krazek(sf::Color color,sf::Vector2f start)
{
	this->color = color;
	this->start = start;
	init();
}
void Krazek::init()
{
	krazek.setFillColor(this->color);
	krazek.setPosition(this->start);
	krazek.setRadius(50);
	kierunek = sf::Vector2f(0, 0);
	przyspieszenie = 1;
	predkosc = 10;
}

Krazek::~Krazek()
{
}

void Krazek::setPredkosc(sf::Vector2f kierunek)
{
	this->kierunek = kierunek;
}

void Krazek::setPrzyspieszenie(float przyspieszenie)
{
	this->przyspieszenie = przyspieszenie;
}

void Krazek::setPredkosc(float predkosc)
{
	this->predkosc = predkosc;
}

void Krazek::move()
{

}

void Krazek::rysuj(sf::RenderWindow * window)
{
	move();
	window->draw(krazek);
}

