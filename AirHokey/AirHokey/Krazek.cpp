#include "Krazek.h"
#include "SFML/Graphics.hpp"
#include "Plansza.h"


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
	krazek.setRadius(30);
	kierunek = sf::Vector2f(0, 0);
	maxpredkosc = 10;
}

Krazek::~Krazek()
{
}

void Krazek::setPredkosc(sf::Vector2f kierunek)
{
	this->kierunek = kierunek;
}

void Krazek::move()
{	
	//printf("%f x %f",kierunek.x,kierunek.y);
	if (kierunek.x != 0 && kierunek.y != 0)
	{
		float predkosc = sqrtf(kierunek.x*kierunek.x + kierunek.y*kierunek.y);
		if (predkosc > maxpredkosc)
		{
			kierunek.x = kierunek.x*0.95f;
			kierunek.y = kierunek.y*0.95f;
		}
			
		
	krazek.move(kierunek.x ,kierunek.y);
	}
}

void Krazek::rysuj(sf::RenderWindow * window)
{
	window->draw(krazek);
}
sf::CircleShape Krazek::zwroc()
{
	return krazek;
}
void Krazek::gol(sf::Vector2f srodek)
{
	krazek.setPosition(srodek);
	kierunek = sf::Vector2f(0,0);
}
sf::Vector2f Krazek::getPredkosc()
{
	return kierunek;
}
