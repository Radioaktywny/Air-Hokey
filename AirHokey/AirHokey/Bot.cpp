#include "Bot.h"


#include "SFML/Graphics.hpp"
#include <iostream>

	
	
	
	Bot::Bot(std::string polowa)
	{
		this->krazek.setFillColor(sf::Color::Magenta);
		this->krazek.setRadius(40);
		if (polowa == "prawo")
		{
			this->krazek.setPosition(1000, 500);
	
		}
		else
		{
			this->krazek.setPosition(100, 100);
		}
		//this->krazek.setPosition(100, 100);
		this->polowa = polowa;
		printf("ustawiam bota: %s", this->polowa.c_str());
		//std::count << "ustawiam bota na polowie : ";// << this->polowa;
	}

	

	Bot::~Bot()
	{
	}

	void Bot::move(sf::Vector2f dir)
	{
		this->kierunek = dir - krazek.getPosition();
		this->kierunek = sf::Vector2f(kierunek.x - krazek.getRadius(), kierunek.y - krazek.getRadius());
		krazek.move(kierunek.x, kierunek.y);
		
	}

	void Bot::rysuj(sf::RenderWindow * window)
	{
		window->draw(this->krazek);
	}

	sf::Vector2f Bot::getKierunek()
	{
		return kierunek;
	}

	sf::CircleShape Bot::getShape()
	{
		return this->krazek;
	}