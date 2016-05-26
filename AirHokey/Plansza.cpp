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
	const int y = 150; // doda³em zmiane polozenia planszy zeby byly na gorze dodac score 
	boisko.setFillColor(color);
	boisko.setPosition(50, y);
	boisko.setSize(wymiary);
	for (int i = 0; i < 4; ++i)
	{
		linieboczne[i].setFillColor(sf::Color::White);
	}
	linieboczne[0].setSize(sf::Vector2f(wymiary.x ,20));
	linieboczne[1].setSize(sf::Vector2f(wymiary.x, 20));
	linieboczne[2].setSize(sf::Vector2f(20, wymiary.y));
	linieboczne[3].setSize(sf::Vector2f(20, wymiary.y));
	linieboczne[0].setPosition(sf::Vector2f(50, y));
	linieboczne[1].setPosition(sf::Vector2f( 50, wymiary.y+(y-20)));
	linieboczne[2].setPosition(sf::Vector2f(50, y));
	linieboczne[3].setPosition(sf::Vector2f(wymiary.x+50, y));
	bramki[0].setFillColor(sf::Color::Red);
	bramki[1].setFillColor(sf::Color::Red);
	bramki[0].setSize(sf::Vector2f(20, wymiary.y/3+30));
	bramki[1].setSize(sf::Vector2f(20, wymiary.y/3+30));
	bramki[0].setPosition(50,wymiary.y/3+y);
	bramki[1].setPosition(wymiary.x+50,wymiary.y/3+y);
	bramka = sf::Vector2f(wymiary.x, wymiary.y / 2);

}
void Plansza::rysuj(sf::RenderWindow* window)
{
	window->draw(boisko);
	for (int i = 0; i < 4; ++i)
		window->draw(linieboczne[i]);
	for (int i = 0; i < 2; ++i)
		window->draw(bramki[i]);
}
short Plansza::czyWplanszy(Krazek* object)
{
	for (int i = 0; i < 4;++i)
	{
		if (linieboczne[i].getGlobalBounds().intersects(object->zwroc().getGlobalBounds()))
		{

			if (i == 0 &&object->getPredkosc().y<0)
			{
				object->setPredkosc(sf::Vector2f(object->getPredkosc().x, -1 * object->getPredkosc().y));
				return 5;
			}
			if (i == 1 && object->getPredkosc().y>0)
			{
				object->setPredkosc(sf::Vector2f(object->getPredkosc().x, -1 * object->getPredkosc().y));
				return 5;
			}
			if(i==2 && object->getPredkosc().x<0)
			{
				object->setPredkosc(sf::Vector2f(-1 * object->getPredkosc().x, object->getPredkosc().y));
				return 5;
			}
			if (i == 3 && object->getPredkosc().x > 0)
			{
				object->setPredkosc(sf::Vector2f(-1 * object->getPredkosc().x, object->getPredkosc().y));
				return 5;
			}
			
		}
		if (i < 2)
		{
			if (bramki[i].getGlobalBounds().intersects(object->zwroc().getGlobalBounds()))
			{
				object->gol(this->getSrodek());
				return (i+1);
			}
		}
	}
	return false;
}
sf::Vector2f Plansza::getSrodek()
{
	return sf::Vector2f(wymiary.x/2,wymiary.y/2);
}
Plansza::~Plansza()
{

}
