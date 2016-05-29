#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include "Plansza.h"
#include "Gracz.h"
#include "Krazek.h"
#include "Kolizje.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Hockey", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	Plansza plansza(sf::Vector2f(1500, 600), sf::Color(100, 200, 200));
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60);
	Gracz gracz1;
	Krazek krazek;
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);
	sf::Vector2f myszka(0, 0);
	//this while loop will only be called if the window is open.
	while (window.isOpen())
	{
		//myszka = sf::Vector2f(krazek.zwroc().getPosition().x-krazek.zwroc().getRadius(), krazek.zwroc().getPosition().y - krazek.zwroc().getRadius());

		sf::Event eventSF;
		while (window.pollEvent(eventSF))
		{
			switch (eventSF.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
			myszka = sf::Vector2f(eventSF.mouseMove.x, eventSF.mouseMove.y);
		}
		accumulator -= ups;
		gracz1.move(myszka);
		if (Kolizje::sprawdzKolizje(&gracz1.getShape(), &krazek.zwroc()))
		{
			sf::Vector2f odbicie = Kolizje::wyznaczPredkosc(&gracz1.getShape(), &krazek.zwroc());
			krazek.setPredkosc(sf::Vector2f(gracz1.getKierunek().x + (krazek.getPredkosc().x*odbicie.x) + krazek.getPredkosc().x, gracz1.getKierunek().y + (krazek.getPredkosc().y*odbicie.y) + krazek.getPredkosc().y));
		}
		plansza.czyWplanszy(&krazek);
		krazek.move();
		
	
	window.clear();
	plansza.rysuj(&window);
	gracz1.rysuj(&window);
	krazek.rysuj(&window);
	window.display();


	accumulator += clock.restart();
}
}