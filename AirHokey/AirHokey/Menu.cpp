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
	Text title("AIR_HOCKEY", font, 80);//tytu�
	title.setStyle(Text::Bold);
	title.setPosition(1600 / 2 - title.getGlobalBounds().width / 2, 20);
	const int ile = 4;
	Text tekst[ile]; // teksty przycisk�w
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
			//Wci�ni�cie ESC 
			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = END;
			//klikni�cie Server
			else if (tekst[0].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GAME_MULTI;
				multiType = SERVER;
				std::cout << "heheheheh jestem w serwerze " + multiType;

			}
			//klikni�cie Klient
			else if (tekst[1].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GAME_MULTI;
				multiType = CLIENT;
			}//klikni�cie Exit
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
	
	Text title("AIR_HOCKEY", font, 80);//tytu�
	title.setStyle(Text::Bold);
	title.setPosition(1600 / 2 - title.getGlobalBounds().width / 2, 20);
	const int ile = 3;
	Text tekst[ile]; // teksty przycisk�w
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
			//Wci�ni�cie ESC 
			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = END;
			//klikni�cie Singleplayer
			else if (tekst[0].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				//state = END;
				state = GAME_SINGLE;
			}
			//klikni�cie Multiplayer
			else if (tekst[1].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = MENU2;
			}//klikni�cie Exit
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
	Gracz gracz(1), gracz2(2);
	Krazek krazek;
	Time accumulator = Time::Zero;
	Time ups = seconds(1.f / 60.f);
	Vector2f myszka(0, 0);
	Clock clock;
	IpAddress ipAddress = IpAddress::getLocalAddress();
	UdpSocket socket;
	unsigned short portServer = 54321;
	unsigned short portClient = 54322;
	Packet packet, receivePacket, sendPacket;
	window.setMouseCursorVisible(false);
	int mouseMoveX;
	int mouseMoveY;
	bool flag = true;
	bool bind = false;

	while (state == GAME_MULTI)
	{
		Event eventSF;
		
		while (window.pollEvent(eventSF))
		{
			switch (eventSF.type)
			{
				case Event::Closed:
					state = MENU;
					window.setMouseCursorVisible(true);
					break;
				case Event::KeyPressed:
					if (eventSF.key.code == Keyboard::Escape)
					{
						state = MENU;
						cout << "Zamykam gre" << endl;
						window.setMouseCursorVisible(true);
					}
					break;
				case Event::MouseMoved:
					break;
			}
		}

		switch (multiType)
		{
			case MultiType::SERVER:
			{
				if (!bind)
				{
					socket.bind(portServer);
					bind = true;
					cout << "binduje";
				}
				string recive, sent;
				sent = "hello client";

				while (flag)
				{
					socket.receive(receivePacket, ipAddress, portClient);
					if (receivePacket >> recive && recive == "hello server")
					{
						flag = false;
						sendPacket << sent;
						socket.send(sendPacket, ipAddress, portClient);
						receivePacket.clear();
						sendPacket.clear();
						cout << "styklo";
					}
				} 

				cout << "stacja 1" << endl;

				gracz.move(Vector2f(eventSF.mouseMove.x, eventSF.mouseMove.y));
				sendPacket << eventSF.mouseMove.x << eventSF.mouseMove.y;
				socket.send(sendPacket, ipAddress, portClient);
				sendPacket.clear();

				socket.receive(receivePacket, ipAddress, portClient);
				while ((receivePacket >> mouseMoveX >> mouseMoveY && receivePacket != NULL))
				{
					gracz2.move(Vector2f(mouseMoveX, mouseMoveY));
					cout << "stacja 2" << endl;
					receivePacket.clear();
				} 

				

				
				cout << "stacja 3" << endl;
				

				if (Kolizje::sprawdzKolizje(&gracz.getShape(), &krazek.zwroc()))
				{
					Vector2f odbicie = Kolizje::wyznaczPredkosc(&gracz.getShape(), &krazek.zwroc());
					krazek.setPredkosc(odbicie);
				}
				break;
			}
			case MultiType::CLIENT:
			{
				if (!bind)
				{
					socket.bind(portClient);
					bind = true;
					cout << "binduje";
				}
				string recive, sent;
				sent = "hello server";
				sendPacket << sent;
				while (flag)
				{
					socket.send(sendPacket, ipAddress, portServer);
					socket.receive(receivePacket, ipAddress, portServer);
					if (receivePacket >> recive && recive == "hello client")
					{
						flag = false;
						receivePacket.clear();
						sendPacket.clear();
						cout << "styklo";
					}
				} 

				cout << "stacja 1"<<endl;
				socket.receive(sendPacket, ipAddress, portClient);
				while (sendPacket >> mouseMoveX >> mouseMoveY && sendPacket != NULL)
				{
					gracz.move(Vector2f(mouseMoveX, mouseMoveY));
					cout << "stacja 2" << endl;
					sendPacket.clear();
				} 
				cout << "stacja 3" << endl;
				
				gracz2.move(Vector2f(eventSF.mouseMove.x, eventSF.mouseMove.y));
				receivePacket << eventSF.mouseMove.x << eventSF.mouseMove.y;
				socket.send(receivePacket, ipAddress, portClient);
				receivePacket.clear();
				
				cout << "stacja 4" << endl;
				if (Kolizje::sprawdzKolizje(&gracz2.getShape(), &krazek.zwroc()))
				{
					Vector2f odbicie = Kolizje::wyznaczPredkosc(&gracz2.getShape(), &krazek.zwroc());
					krazek.setPredkosc(odbicie);
				}
				break;
			}
		}
		krazek.move();
		plansza.czyWplanszy(&krazek);
		while (accumulator > ups)
		{
			accumulator -= ups;
			window.clear();
			plansza.rysuj(&window);
			krazek.rysuj(&window);
			gracz.rysuj(&window);
			gracz2.rysuj(&window);
			window.display();
		}
		accumulator += clock.restart();
	}
}
