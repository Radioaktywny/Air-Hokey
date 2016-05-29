#include "SinglePlayer.h"
#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include <iomanip>
#include "Plansza.h"
#include "Gracz.h"
#include "Krazek.h"
#include "Bot.h"
#include "Menu.h"
#include "Kolizje.h"
#include "Score.h"


SinglePlayer::SinglePlayer()//RenderWindow * window , Font font)
{	
}


SinglePlayer::~SinglePlayer()
{
}

string SinglePlayer::run(RenderWindow * window , Font *font , string *wygral)
{
	window->setMouseCursorVisible(false);
	Score wynik(font);
	int szerokosc = 1500;
	int wysokosc = 600;
	Plansza plansza(sf::Vector2f(szerokosc, wysokosc), sf::Color(100, 200, 200));
	Gracz gracz1;
	Krazek krazek;
	string strona_bota = "prawa";
	Bot bot(strona_bota, &plansza, &krazek); // bedzie botem
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);
	sf::Vector2f myszka(0, 0);
	sf::Clock clock;
	while (true)
	{
		if (wynik.czy_koniec() == "koniec")
		{
			wynik.wyznaczWygranego(&strona_bota , wygral);
			window->setMouseCursorVisible(true);
			return "GAME_OVER";
		}
		//Define the event variable
		sf::Event eventSF;

		//Check if there is an event
		while (window->pollEvent(eventSF))
		{

			switch (eventSF.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::KeyPressed:
				if (eventSF.key.code == Keyboard::Escape)
				{
					
					cout << "Zamykam gre" << endl;
					window->setMouseCursorVisible(true);
					return "MENU";
				}
				break;
			case sf::Event::MouseMoved:
				//	gracz1.move(sf::Vector2f(eventSF.mouseMove.x, eventSF.mouseMove.y));
				break;
			}
		}


		if (Kolizje::sprawdzKolizje(&gracz1.getShape(), &krazek.zwroc()))
		{
			sf::Vector2f odbicie = Kolizje::wyznaczPredkosc(&gracz1.getShape(), &krazek.zwroc());
			//	krazek.setPredkosc(sf::Vector2f(gracz1.getKierunek().x + (krazek.getPredkosc().x*odbicie.x) + krazek.getPredkosc().x, gracz1.getKierunek().y + (krazek.getPredkosc().y*odbicie.y) + krazek.getPredkosc().y));
			krazek.setPredkosc(odbicie);
			//		krazek.setPredkosc(sf::Vector2f(gracz1.getKierunek().x, gracz1.getKierunek().y));
			//	gracz1.move(sf::Vector2f(0.0000000000000000000000000001f, 0.0000000000000000000000001f));

		}

		else if (Kolizje::sprawdzKolizje(&bot.getShape(), &krazek.zwroc()))
		{
			sf::Vector2f odbicie = Kolizje::wyznaczPredkosc(&bot.getShape(), &krazek.zwroc());
			krazek.setPredkosc(odbicie);
			bot.juzuderzylem(); // to powinno byc w bocie
								//	krazek.setPredkosc(sf::Vector2f(bot.getKierunek().x,bot.getKierunek().y));
								//	bot.moveTo(0.4f,0.4f);
								//	krazek.setPredkosc(sf::Vector2f(bot.getKierunek().x + (krazek.getPredkosc().x*odbicie.x) + krazek.getPredkosc().x, bot.getKierunek().y + (krazek.getPredkosc().y*odbicie.y) + krazek.getPredkosc().y));

		}
		else
		{

			//do wywalenia chyba ze zmieniamy opóŸnienie na myszce

		}
		gracz1.move(sf::Vector2f(eventSF.mouseMove.x, eventSF.mouseMove.y));
		bot.move();
		int sprawdz = plansza.czyWplanszy(&krazek);
		if (sprawdz == 5)//najechal na sciane boczna
		{
			//slabe obejscie problemu 
		}
		else if (sprawdz == 1) // trafil w bramke
		{
			//std::cout << "trafil1" << std::endl;
			wynik.SetScore(0);
		}
		else if (sprawdz == 2) // trafil w bramke
		{
			//	std::cout << "trafil0" << std::endl;
			wynik.SetScore(1);
		}
		else
		{
			krazek.move();
		}

		while (accumulator > ups)
		{
			accumulator -= ups;

			window->clear();
			plansza.rysuj(window);
			krazek.rysuj(window);
			bot.rysuj(window);//bot bedzie
			gracz1.rysuj(window);
			wynik.rysuj(window);
			window->display();
		}
		accumulator += clock.restart();
	}
	return "";
}
