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

RenderWindow window(VideoMode(1600, 900), "Hockey", Style::Titlebar | Style::Close | Style::Resize);

Menu::Menu()
{
	state = END;
	if (!font.loadFromFile("data/Mecha.ttf"))
	{
		MessageBox(NULL, "Font not found!", "ERROR", NULL);
		return;
	}
	state = MENU;
	runMenu();
}


Menu::~Menu()
{
}

void Menu::runMenu()
{
	//dopoki nie ma statusu END	
	while (state != END)
	{
		switch (state)
		{
		case MenuState::MENU:
			menus();
			break;
		case MenuState::MENU2:
			menusMulti();
			break;
		case MenuState::GAME_MULTI:
			Multiplayer();
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

void Menu::menusMulti()
{
	Text title("AIR_HOCKEY", font, 80);//tytu³
	title.setStyle(Text::Bold);
	title.setPosition(1600 / 2 - title.getGlobalBounds().width / 2, 20);
	const int ile = 4;
	Text tekst[ile]; // teksty przycisków
	string str[] = { "Server" , "Client", "Back", "Exit" };
	for (int i = 0; i < ile; i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(65);
		tekst[i].setString(str[i]);
		tekst[i].setPosition(1600 / 2 - tekst[i].getGlobalBounds().width / 2, 250 + i * 120);
	}

	while (state == MENU2)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;

		while (window.pollEvent(event))
		{
			//Wciœniêcie ESC 
			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = END;
			//klikniêcie Server
			else if (tekst[0].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GAME_MULTI;
			}
			//klikniêcie Klient
			else if (tekst[1].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GAME_MULTI;
			}//klikniêcie Exit
			else if (tekst[2].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = MENU;
			}
			else if (tekst[3].getGlobalBounds().contains(mouse) &&
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
		Vector2f mouse(Mouse::getPosition(window));
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
				state = MENU2;
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
	Bot bot("prawa", &plansza, &krazek); // bedzie botem
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);
	sf::Vector2f myszka(0, 0);
	sf::Clock clock;
	window.setMouseCursorVisible(false);

	//Dopuki gra
	while (state == GAME_SINGLE)
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
			krazek.setPredkosc(odbicie);
		}

		else if (Kolizje::sprawdzKolizje(&bot.getShape(), &krazek.zwroc()))
		{
			sf::Vector2f odbicie = Kolizje::wyznaczPredkosc(&bot.getShape(), &krazek.zwroc());
			krazek.setPredkosc(odbicie);

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

void Menu::Multiplayer()
{
	int szerokosc = 1500;
	int wysokosc = 600;
	Plansza plansza(Vector2f(szerokosc, wysokosc), Color(100, 200, 200));
	Gracz gracz;
	Krazek krazek;
	Time accumulator = Time::Zero;
	Time ups = seconds(1.f / 60.f);
	Vector2f myszka(0, 0);
	Clock clock;
	window.setMouseCursorVisible(false);

	while (state == GAME_MULTI)
	{
		//Define the event variable
		Event eventSF;

		//Check if there is an event
		while (accumulator > ups)
		{
			accumulator -= ups;
		}
		while (window.pollEvent(eventSF))
		{

			switch (eventSF.type)
			{
			case Event::Closed:
				window.close();
				state = MENU;
				break;
			case Event::KeyPressed:
				if (eventSF.key.code == Keyboard::Escape)
				{
					state = MENU;
					cout << "Zamykam gre" << endl;
					window.setMouseCursorVisible(true);
				}
				break;
			case sf::Event::MouseMoved:
				break;
			}
		}
		if (Kolizje::sprawdzKolizje(&gracz.getShape(), &krazek.zwroc()))
		{
			sf::Vector2f odbicie = Kolizje::wyznaczPredkosc(&gracz.getShape(), &krazek.zwroc());		
			krazek.setPredkosc(odbicie);

		}
		else
		{
			gracz.move(sf::Vector2f(eventSF.mouseMove.x, eventSF.mouseMove.y));
			

		}
		window.clear();
		krazek.move();

		plansza.czyWplanszy(&krazek);
		plansza.rysuj(&window);
		krazek.rysuj(&window);
		gracz.rysuj(&window);
		window.display();
		accumulator += clock.restart();
	}
}
