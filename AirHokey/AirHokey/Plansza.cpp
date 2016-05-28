#include "Plansza.h"
#include "SFML/Graphics.hpp"
#include "Krazek.h"
#include "Kolizje.h"

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
	linieboczne[0].setSize(sf::Vector2f(wymiary.x ,30));
	linieboczne[1].setSize(sf::Vector2f(wymiary.x, 30));
	linieboczne[2].setSize(sf::Vector2f(30,( wymiary.y / 3) - 15));
	linieboczne[3].setSize(sf::Vector2f(30, (wymiary.y / 3) - 15));
	linieboczne[4].setSize(sf::Vector2f(30, (wymiary.y / 3) - 15));
	linieboczne[5].setSize(sf::Vector2f(30, (wymiary.y / 3) - 15));
	linieboczne[0].setPosition(sf::Vector2f(50, y));
	linieboczne[1].setPosition(sf::Vector2f( 50, wymiary.y+(y-30)));
	linieboczne[2].setPosition(sf::Vector2f(50, y));
	linieboczne[3].setPosition(sf::Vector2f(wymiary.x+20, y));
	linieboczne[4].setPosition(sf::Vector2f(50, (y+(wymiary.y/3)*2)+15));
	linieboczne[5].setPosition(sf::Vector2f(wymiary.x + 20, (y + (wymiary.y / 3) * 2) + 15));
	for (int i = 0; i < 4; ++i)
	{
		slupki[i].setFillColor(sf::Color::White);
		slupki[i].setRadius(15);
	}
	slupki[0].setPosition(50, y+ (wymiary.y / 3) - 29);
	slupki[1].setPosition(50, y -1+ (wymiary.y / 3)*2);
	slupki[2].setPosition(wymiary.x + 20, y + (wymiary.y / 3) - 29);
	slupki[3].setPosition(wymiary.x + 20, y-1 + (wymiary.y / 3*2) );
	//bramki[0].setFillColor(sf::Color::Red);
	//bramki[1].setFillColor(sf::Color::Red);
	bramki[0].setSize(sf::Vector2f(20, wymiary.y/3));
	bramki[1].setSize(sf::Vector2f(20, wymiary.y/3));
	bramki[0].setPosition(5,wymiary.y/3+y);
	bramki[1].setPosition(wymiary.x+85,wymiary.y/3+y);
	bramka = sf::Vector2f(wymiary.x, wymiary.y / 2);

}
void Plansza::rysuj(sf::RenderWindow* window)
{
	window->draw(boisko);
	for (int i = 0; i < 6; ++i)
		window->draw(linieboczne[i]);
	//for (int i = 0; i < 2; ++i)
		//window->draw(bramki[i]);
	for (int i = 0; i < 4; ++i)	
		window->draw(slupki[i]);
	
}
short Plansza::czyWplanszy(Krazek* object)
{
	for (int i = 0; i < 6;++i)
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
			if((i==2||i==4) && object->getPredkosc().x<0)
			{
				object->setPredkosc(sf::Vector2f(-1 * object->getPredkosc().x, object->getPredkosc().y));
				return 5;
			}
			if ((i == 3 || i == 5) && object->getPredkosc().x > 0)
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
	for (int i = 0; i < 4; ++i)
	{
		if (Kolizje::sprawdzKolizje(&slupki[i], &object->zwroc()))
			object->setPredkosc(Kolizje::wyznaczPredkosc(&slupki[i], &object->zwroc()));
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
