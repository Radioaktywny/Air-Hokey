#include "Plansza.h"
#include "SFML/Graphics.hpp"
#include "Krazek.h"

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
	for (int i = 0; i < 4; ++i)
	{
		linieboczne[i].setFillColor(sf::Color::White);
	}
	linieboczne[0].setSize(sf::Vector2f(wymiary.x ,20));
	linieboczne[1].setSize(sf::Vector2f(wymiary.x, 20));
	linieboczne[2].setSize(sf::Vector2f(20, wymiary.y));
	linieboczne[3].setSize(sf::Vector2f(20, wymiary.y));
	linieboczne[0].setPosition(sf::Vector2f(50, 50));
	linieboczne[1].setPosition(sf::Vector2f( 50, wymiary.y+30));
	linieboczne[2].setPosition(sf::Vector2f(50, 50));
	linieboczne[3].setPosition(sf::Vector2f(wymiary.x+50, 50));



}
void Plansza::rysuj(sf::RenderWindow* window)
{
	window->draw(boisko);
	for (int i = 0; i < 4; ++i)
		window->draw(linieboczne[i]);
}
void Plansza::czyWplanszy(Krazek* object)
{
	for (int i = 0; i < 4;++i)
	{
		if (linieboczne[i].getGlobalBounds().intersects(object->zwroc()))
		{
			printf("WSZEDLEM");

			if (i == 0 &&object->getPredkosc().y<0)
			{
				printf("dolna gorna");
				object->setPredkosc(sf::Vector2f(object->getPredkosc().x, -1 * object->getPredkosc().y));
			}
			if (i == 1 && object->getPredkosc().y>0)
			{
				printf("dolna gorna");
				object->setPredkosc(sf::Vector2f(object->getPredkosc().x, -1 * object->getPredkosc().y));
			}
			else
			{
				printf("prawa lewa");
				object->setPredkosc(sf::Vector2f(-1 * object->getPredkosc().x, object->getPredkosc().y));
			}
		}
	}
}
Plansza::~Plansza()
{

}
