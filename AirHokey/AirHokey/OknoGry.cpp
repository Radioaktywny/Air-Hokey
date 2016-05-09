#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include "Plansza.h"
#include "Gracz.h"
#include "Krazek.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Hockey", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize); 
	Plansza plansza(sf::Vector2f(1500, 600), sf::Color(100, 200, 200));
	Gracz gracz1;
	Krazek krazek;
	//this while loop will only be called if the window is open.
	while (window.isOpen())
	{
		//Define the event variable
		sf::Event eventSF;
		//Check if there is an event
		while (window.pollEvent(eventSF))
		{

			switch (eventSF.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseEntered:
				std::cout << "Mouse within screen bounds" << std::endl;
				break;
			case sf::Event::MouseLeft:
				std::cout << "Mouse outisde the screen bounds" << std::endl;
				break;
			case sf::Event::MouseMoved:				
				gracz1.move(sf::Vector2f(eventSF.mouseMove.x, eventSF.mouseMove.y));
				break;
			}
				
		}
		window.clear();
		plansza.rysuj(&window);
		//if (plansza.czyWplanszy(gracz1.getShape()))
		krazek.rysuj(&window);
		gracz1.rysuj(&window);
		window.display();

	}
}