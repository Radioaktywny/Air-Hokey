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
sf::RenderWindow window(sf::VideoMode(1600, 900), "Hockey", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
Menu::Menu()
{
	state = END;
	if (!font.loadFromFile("data/Mecha.ttf"))
	{
		MessageBox(NULL, "Font not found!", "ERROR", NULL);
		return;
	}
	state = MENU;
}


Menu::~Menu()
{
}



void Menu::runMenu()
{
	//dopuki nie ma statusu END	
	while (state != END)
	{
		switch (state)
		{
		case MenuState::MENU:
			menus();
			break;
		case MenuState::GAME_MULTI:
			//odpala MULTI
			cout<<"Odpalam Multiplayera"<<endl;
			state = MENU; // narazie wraca do menu
			break;
		
		case MenuState::GAME_SINGLE:
			//odpala SINGLA
			Singleplayer();
			cout << "Odpalam Singleplayera" << endl;
			menus();
			break;
		}
	}
}


void Menu::menus()
{	
	
	Text title("AIR_HOCKEY", font, 80);//tytu³
	title.setStyle(Text::Bold);
	title.setPosition(1600 / 2 - title.getGlobalBounds().width / 2, 20);
	const int ile = 3;
	Text tekst[ile]; // teksty przycisków
	string str[] = { "SinglePlayer" , "MultiPlayer","Exit" };
	for (int i = 0; i < ile; i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(65);
		tekst[i].setString(str[i]);
		tekst[i].setPosition(1600 / 2 - tekst[i].getGlobalBounds().width / 2, 250 + i * 120);
	}

	while (state == MENU)
	{
		sf::Vector2f mouse(Mouse::getPosition(window));
		Event event;

		while (window.pollEvent(event))
		{
			//Wciœniêcie ESC 
			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = END;
			//klikniêcie Singleplayer
			else if (tekst[0].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				//state = END;
				state = GAME_SINGLE;
			}
			//klikniêcie Multiplayer
			else if (tekst[1].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GAME_MULTI;
			}//klikniêcie Exit
			else if (tekst[2].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = END;
			}
		}

		//kolory jak najedziesz
		for (int i = 0; i < ile; i++)
			if (tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setColor(Color::Red);
			else tekst[i].setColor(Color::White);

			window.clear();

			window.draw(title);
			for (int i = 0; i < ile; i++)
				window.draw(tekst[i]);
			window.display();
	}
}

void Menu::Singleplayer()
{
	int szerokosc = 1500;
	int wysokosc = 600;
	Plansza plansza(sf::Vector2f(szerokosc, wysokosc), sf::Color(100, 200, 200));
	Gracz gracz1;
	Krazek krazek;
	Bot bot("prawa", &plansza , &krazek); // bedzie botem
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);
	sf::Vector2f myszka(0, 0);
	sf::Clock clock;
	window.setMouseCursorVisible(false);
	
	//Dopuki gra
	while (state == GAME_SINGLE )
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
			case sf::Event::KeyPressed:
				if (eventSF.key.code == Keyboard::Escape)
				{
					state = MENU;
					cout << "Zamykam gre" << endl;
					window.setMouseCursorVisible(true);
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
					bot.juzuderzylem();
					//	krazek.setPredkosc(sf::Vector2f(bot.getKierunek().x,bot.getKierunek().y));
				//	bot.moveTo(0.4f,0.4f);
					//	krazek.setPredkosc(sf::Vector2f(bot.getKierunek().x + (krazek.getPredkosc().x*odbicie.x) + krazek.getPredkosc().x, bot.getKierunek().y + (krazek.getPredkosc().y*odbicie.y) + krazek.getPredkosc().y));

				}
				else
				{
					
					

				}
				gracz1.move(sf::Vector2f(eventSF.mouseMove.x, eventSF.mouseMove.y));
				bot.move();
				krazek.move();
				plansza.czyWplanszy(&krazek);
				while (accumulator > ups)
				{
					accumulator -= ups;
				
			window.clear();
			plansza.rysuj(&window);
			krazek.rysuj(&window);
			bot.rysuj(&window);//bot bedzie
			gracz1.rysuj(&window);
			window.display();
				}
			accumulator += clock.restart();
	}
}
