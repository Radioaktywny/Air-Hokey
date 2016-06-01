#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
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
#include "ConnectionMenu.h"
#include "Multiplayer.h"

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
	while (state != END)
	{
		switch (state)
		{
		case MenuState::MENU:
			menuGlowne();
			break;

		case MenuState::CONN_MULTI:
			//odpala podmenu multi
			cout<<"podmenu multi"<<endl;
			menuPolaczenieMulti();
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

		case MenuState::SERVER:
			//odpala multi jako server
			cout << "Server Start" << endl;
			multiplayerServer();
			break;

		case MenuState::CLIENT:
			//odpala multi jako client
			cout << "Client Start" << endl;
			multiplayerClient();
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

void Menu::menuPolaczenieMulti()
{
	ConnectionMenu conn;
	String bedzie = conn.run(&window, &font);
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

void Menu::multiplayerServer()
{
	Multiplayer multiServ;
	String bedzie = multiServ.run(&window, &font, &wygral, "SERVER");
	state_update(bedzie);
}

void Menu::multiplayerClient()
{
	Multiplayer multiCli;
	String bedzie = multiCli.run(&window, &font, &wygral, "CLIENT");
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
	else if (bedzie == "SERVER")
	{
		state = SERVER;
	}
	else if (bedzie == "CLIENT")
	{
		state = CLIENT;
	}
	else if (bedzie == "GAME_OVER")
	{
		state = GAME_OVER;
	}
	else if (bedzie == "CONN_MULTI")
	{
		state = CONN_MULTI;
	}
}
	
