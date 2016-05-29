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
#include "MenuGlowne.h"
sf::RenderWindow window(sf::VideoMode(1600, 900), "Hockey", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
Menu::Menu()
{
	state = END;
	if (!font.loadFromFile("data/Mecha.ttf"))
	{
		MessageBoxA(NULL, "Font not found!", "ERROR", NULL);
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
	MenuGlowne menus;
	String bedzie = menus.run(&window, &font);
	state_update(bedzie);
}

void Menu::menuKoniecGry()
{
	GameOver over;
	String bedzie = over.run(&window, &font, &wygral);
	state_update(bedzie);
	
}

void Menu::singleplayer()
{
	SinglePlayer single;
	String bedzie = single.run(&window, &font , &wygral);
	state_update(bedzie);
}

void Menu::state_update(String bedzie)
{
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
	else if (bedzie == "GAME_MULTI")
	{
		state = GAME_SINGLE;
	}
	else if (bedzie == "GAME_OVER")
	{
		state = GAME_OVER;
	}
}
	

