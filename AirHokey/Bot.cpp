#include "Bot.h"
#include "Plansza.h"
#include "SFML/Graphics.hpp"


	
	
	
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
			linia_przy_bramce=linia_przy_bramce - 50;//przy 100 za duza przerwa :/
			this->krazek.setPosition((plansza->linieboczne[1].getPosition().x + this->linia_przy_bramce) / 2, plansza->linieboczne[1].getPosition().y / 2);
		//	this->krazek.setPosition(500, 500);
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

	void Bot::moveTo(float x, float y)
	{

		krazek.move(x, y);
	}

	sf::Vector2f Bot::getKierunek()
	{
		return kierunek;
	}

	sf::CircleShape Bot::getShape()
	{
		return this->krazek;
	}

	void Bot::juzuderzylem()
	{
		uderzylem = true;
	}

	void Bot::move_right_side()
	{	
		if (uderzylem)
		{
			if (static_cast<int>(krazek.getPosition().x) <= plansza->linieboczne[3].getPosition().x - this->linia_przy_bramce) // jezeli pilka nie na polowce i krazek nie na lini startu
			{
				if (krazek.getPosition().y > pilka->zwroc().getPosition().y)
				{
					krazek.move(speed_do_lini, -speed_do_lini);
				}
				else if (krazek.getPosition().y < pilka->zwroc().getPosition().y)
				{
					krazek.move(speed_do_lini, speed_do_lini);
				}

			}
			else
			{
				if (krazek.getPosition().y > pilka->zwroc().getPosition().y)
				{
					krazek.move(0, +speed_do_lini);
				}
				else if (krazek.getPosition().y < pilka->zwroc().getPosition().y)
				{
					krazek.move(0, -speed_do_lini);
				}
				uderzylem = false;
			}

		}
		else
		{
				
		//std::cout << krazek.getPosition().x << " : " << plansza->linieboczne[3].getPosition().x<<std::endl;
		float problem_ze_stackiem = 40;//nie rozwiazuje :/
		if (pilka->zwroc().getPosition().x > plansza->getSrodek().x)//jezeli pilka jest na polowie krazka
		{
			if (krazek.getPosition().x > pilka->zwroc().getPosition().x- problem_ze_stackiem)
			{
				if (krazek.getPosition().y > pilka->zwroc().getPosition().y + problem_ze_stackiem)
				{
					krazek.move(-speed_do_krazka, -speed_do_krazka);
				}
				else if (krazek.getPosition().y < pilka->zwroc().getPosition().y - problem_ze_stackiem)
				{
					krazek.move(-speed_do_krazka, speed_do_krazka);
				}
			}
			else if (krazek.getPosition().x < pilka->zwroc().getPosition().x+ problem_ze_stackiem)
			{

				if (krazek.getPosition().y > pilka->zwroc().getPosition().y + problem_ze_stackiem)
				{
					krazek.move(speed_do_krazka, -speed_do_krazka);
				}
				else if (krazek.getPosition().y < pilka->zwroc().getPosition().y - problem_ze_stackiem)
				{
					krazek.move(speed_do_krazka, speed_do_krazka);
				}

			}
		}
		else if (static_cast<int>(krazek.getPosition().x) <= plansza->linieboczne[3].getPosition().x - this->linia_przy_bramce) // jezeli pilka nie na polowce i krazek nie na lini startu
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
		
	}

	void Bot::move_left_side()
	{

	//	std::cout << krazek.getPosition().x << " : " << plansza->linieboczne[2].getPosition().x<<std::endl;

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
		else if (static_cast<int>(krazek.getPosition().x) >= plansza->linieboczne[2].getPosition().x + this->linia_przy_bramce) // jezeli pilka nie na polowce i krazek nie na lini startu
		{
			if (krazek.getPosition().y > pilka->zwroc().getPosition().y)
			{
				krazek.move(-speed_do_lini, -speed_do_lini);
			}
			else if (krazek.getPosition().y < pilka->zwroc().getPosition().y)
			{
				krazek.move(-speed_do_lini, speed_do_lini);
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
