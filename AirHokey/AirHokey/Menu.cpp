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
#include "SinglePlayer.h"
#include "GameOver.h"
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
			menuGlowne();
			break;
		case MenuState::GAME_MULTI:
			//odpala MULTI
			cout<<"Odpalam Multiplayera"<<endl;
			state = MENU; // narazie wraca do menu
			menuKoniecGry();
			break;
		
		case MenuState::GAME_SINGLE:
			//odpala SINGLA
			singleplayer();
			cout << "Odpalam Singleplayera" << endl;
			break;
		
		case MenuState::GAME_OVER:
			//odpala Koniec Gry
			cout << "Odpalam Gameover" << endl;
			menuKoniecGry();
			break;
		}
	}
}


void Menu::menuGlowne()
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

void Menu::menuKoniecGry()
{
	GameOver over;
	String bedzie = over.run(&window, &font, &wygral);
	if (bedzie == "END")
	{
		state = END;
	}
	else if (bedzie == "MENU")
	{
		state = MENU;
	}
	else if (bedzie == "GAME_SINGLE")
	{
		state = GAME_SINGLE;
	}
}

void Menu::singleplayer()
{
	SinglePlayer single;
	String bedzie = single.run(&window, &font , &wygral);
	if (bedzie == "GAME_OVER")
	{
		state = GAME_OVER;
	}
	else if (bedzie == "MENU")
	{
		state = MENU;
	}

}
	

