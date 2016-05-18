#include "Bot.h"


#include "SFML/Graphics.hpp"


	
	Bot::Bot()
	{
		this->krazek.setFillColor(sf::Color::Magenta);
		this->krazek.setRadius(40);
		this->krazek.setPosition(100, 100);
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

	sf::CircleShape* Bot::getShape()
	{
		return &krazek;
	}
