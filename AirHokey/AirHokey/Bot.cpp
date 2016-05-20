#include "Bot.h"

#include "Plansza.h"
#include "SFML/Graphics.hpp"
#include <iostream>


	
	
	
	Bot::Bot(std::string polowa ,Plansza *plansza , Krazek * pilka)
	{	
		this->pilka = pilka;
		this->plansza = plansza;
		this->krazek.setFillColor(sf::Color::Magenta);
		this->krazek.setRadius(40);
		if (polowa == "prawa")
		{
			this->krazek.setPosition((plansza->linieboczne[3].getPosition().x - this->linia_przy_bramce) / 2, plansza->linieboczne[3].getPosition().y/2);
		}
		else if(polowa == "lewa")
		{
		//	this->krazek.setPosition((plansza->linieboczne[1].getPosition().x + this->linia_przy_bramce) / 2, plansza->linieboczne[1].getPosition().y / 2);
			this->krazek.setPosition(500, 500);
		}
		//this->krazek.setPosition(100, 100);
		this->polowa = polowa;
		printf("ustawiam bota: %s", this->polowa.c_str());
		//std::count << "ustawiam bota na polowie : ";// << this->polowa;
	}

	

	

	Bot::~Bot()
	{
	}
	int i = 0;
	void Bot::move()
	{
	//	this->kierunek = dir - krazek.getPosition();
	//	this->kierunek = sf::Vector2f(kierunek.x - krazek.getRadius(), kierunek.y - krazek.getRadius());
		if (this->polowa == "prawa")
		{
			move_right_side();
		}
		else
		{
			move_left_side();
		}
		
		
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

	void Bot::move_right_side()
	{	

		
		float speed_do_lini=0.4f;
		float speed_do_krazka = 0.4f;
		//std::cout << krazek.getPosition().x << " : " << plansza->linieboczne[3].getPosition().x<<std::endl;
		
		if (pilka->zwroc().getPosition().x > plansza->getSrodek().x)//jezeli pilka jest na polowie krazka
		{
			if (krazek.getPosition().x > pilka->zwroc().getPosition().x)
			{
				if (krazek.getPosition().y > pilka->zwroc().getPosition().y)
				{
					krazek.move(-speed_do_krazka, -speed_do_krazka);
				}
				else if (krazek.getPosition().y < pilka->zwroc().getPosition().y)
				{
					krazek.move(-speed_do_krazka, speed_do_krazka);
				}
			}
			else if (krazek.getPosition().x < pilka->zwroc().getPosition().x)
			{

				if (krazek.getPosition().y > pilka->zwroc().getPosition().y)
				{
					krazek.move(speed_do_krazka, -speed_do_krazka);
				}
				else if (krazek.getPosition().y < pilka->zwroc().getPosition().y)
				{
					krazek.move(speed_do_krazka, speed_do_krazka);
				}

			}
		}
		else if (static_cast<int>(krazek.getPosition().x) != plansza->linieboczne[3].getPosition().x - this->linia_przy_bramce) // jezeli pilka nie na polowce i krazek nie na lini startu
			{
				if (krazek.getPosition().y > pilka->zwroc().getPosition().y)
				{
					krazek.move(speed_do_lini, -speed_do_lini);
				}
				else if (krazek.getPosition().y < pilka->zwroc().getPosition().y)
				{
					krazek.move(speed_do_lini, speed_do_lini );
				}
				
			}
			else
			{
				if (krazek.getPosition().y > pilka->zwroc().getPosition().y)
				{
					krazek.move(0, -speed_do_lini);
				}
				else if (krazek.getPosition().y < pilka->zwroc().getPosition().y)
				{
					krazek.move(0, speed_do_lini);
				}
			}
		
	}

	void Bot::move_left_side()
	{

		float speed_do_lini = 0.4f;
		float speed_do_krazka = 0.0f;
		std::cout << krazek.getPosition().x << " : " << plansza->linieboczne[2].getPosition().x<<std::endl;

		if (pilka->zwroc().getPosition().x < plansza->getSrodek().x)//jezeli pilka jest na polowie krazka
		{
			if (krazek.getPosition().x > pilka->zwroc().getPosition().x)
			{
				if (krazek.getPosition().y > pilka->zwroc().getPosition().y)
				{
					krazek.move(-speed_do_krazka, speed_do_krazka);
				}
				else if (krazek.getPosition().y < pilka->zwroc().getPosition().y)
				{
					krazek.move(-speed_do_krazka, -speed_do_krazka);
				}
			}
			else if (krazek.getPosition().x < pilka->zwroc().getPosition().x)
			{

				if (krazek.getPosition().y > pilka->zwroc().getPosition().y)
				{
					krazek.move(speed_do_krazka, -speed_do_krazka);
				}
				else if (krazek.getPosition().y < pilka->zwroc().getPosition().y)
				{
					krazek.move(speed_do_krazka, speed_do_krazka);
				}

			}
		}
		else if (static_cast<int>(krazek.getPosition().x) != plansza->linieboczne[2].getPosition().x + this->linia_przy_bramce) // jezeli pilka nie na polowce i krazek nie na lini startu
		{
			if (krazek.getPosition().y > pilka->zwroc().getPosition().y)
			{
				krazek.move(-speed_do_lini, speed_do_lini);
			}
			else if (krazek.getPosition().y < pilka->zwroc().getPosition().y)
			{
				krazek.move(-speed_do_lini, -speed_do_lini);
			}

		}
		else
		{
			if (krazek.getPosition().y > pilka->zwroc().getPosition().y)
			{
				krazek.move(0, speed_do_lini);
			}
			else if (krazek.getPosition().y < pilka->zwroc().getPosition().y)
			{
				krazek.move(0, -speed_do_lini);
			}
		}
	}
