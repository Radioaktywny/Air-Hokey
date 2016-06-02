#include "Multiplayer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
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
//#include <thread>
#include <future>


using namespace sf;

Multiplayer::Multiplayer(RenderWindow * window, Font *font, string *wygral, string state)
{
	this->window = window;
	this->font = font;
	this->wygral = wygral;
	this->state = state;
}

Multiplayer::~Multiplayer()
{
}

string Multiplayer::eventsManage(sf::RenderWindow * window, sf::Event eventSF)
{
	while (window->pollEvent(this->eventSF))
	{
		switch (eventSF.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case Event::KeyPressed:
			if (eventSF.key.code == Keyboard::Escape)
			{
				window->setMouseCursorVisible(true);
				return "MENU";
				window->close();
			}
			break;
		case Event::MouseMoved:
			break;
		}
	}
	return "";
}

Text Multiplayer::mojBaton(string text)
{
	sf::Text clickStart(text, *font, 45);
	clickStart.setStyle(sf::Text::Bold);
	clickStart.setColor(Color::Black);
	clickStart.setPosition(1600 / 2 - clickStart.getGlobalBounds().width / 2, 200);
	return clickStart;
}

string Multiplayer::funkcja(int pyk)
{
	return "";
}
string Multiplayer::run()
{
	this->window->setMouseCursorVisible(false);
	this->window->setFramerateLimit(120);
	Score wynik(font);
	int szerokosc = 1500;
	int wysokosc = 600;
	Plansza plansza(sf::Vector2f(szerokosc, wysokosc), sf::Color(100, 200, 200));
	Gracz server, client;
	Krazek krazek;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);
	sf::Vector2f myszka(0, 0);
	sf::Clock clock;
	sf::IpAddress ipAddress = IpAddress::getLocalAddress();
	sf::UdpSocket socket;
	unsigned short portServer = 54321;
	unsigned short portClient = 54322;
	sf::Packet packet, receivePacket, sendPacket;
	int mouseMoveX, mouseMoveY;
	bool flag = true;
	bool bind = false;
	sf::Event eventSF;
	string client_score = "prawa";
	string server_score = "lewa";
	
	
	while (true)
	{
		this->window->pollEvent(eventSF);
		
		if (eventsManage(window, eventSF) == "MENU")
			return "MENU";
		
		
		if (state == "SERVER")
		{
			if (!bind)
			{
				socket.bind(portServer);
				bind = true;
			}

			if (wynik.czy_koniec() == "koniec")
			{
				wynik.wyznaczWygranego(&client_score, wygral);
				window->setMouseCursorVisible(true);
				return "GAME_OVER_MULTI";
			}

			int recive, sent;
			sent = 69;

			while (flag)
			{
				window->clear();
				server.setPosition(200, 430);
				client.setPosition(1400, 430);
				plansza.rysuj(window);
				krazek.rysuj(window);
				server.rysuj(window);
				client.rysuj(window);
				window->draw(mojBaton("Waiting for client to connect"));
				window->display();

				socket.receive(receivePacket, ipAddress, portClient); 
				if (receivePacket >> recive && recive == 69)
				{
					flag = false;
					sendPacket << sent;
					socket.send(sendPacket, ipAddress, portClient);
					receivePacket.clear();
					sendPacket.clear();
				}
			}

			server.move(Vector2f(eventSF.mouseMove.x, eventSF.mouseMove.y));
			sendPacket << eventSF.mouseMove.x << eventSF.mouseMove.y;
			socket.send(sendPacket, ipAddress, portClient);
			sendPacket.clear();

			socket.receive(receivePacket, ipAddress, portClient);
			while ((receivePacket >> mouseMoveX >> mouseMoveY && receivePacket != NULL))
			{
				client.move(Vector2f(mouseMoveX, mouseMoveY));
				receivePacket.clear();
			}

			if (Kolizje::sprawdzKolizje(&server.getShape(), &krazek.zwroc()))
			{
				krazek.setPredkosc(Kolizje::wyznaczPredkosc(&server.getShape(), &krazek.zwroc()));
			}
			else if (Kolizje::sprawdzKolizje(&client.getShape(), &krazek.zwroc()))
			{
				krazek.setPredkosc(Kolizje::wyznaczPredkosc(&client.getShape(), &krazek.zwroc()));
			}
		}

		else
		{
			if (!bind)
			{
				socket.bind(portClient);
				bind = true;
			}

			if (wynik.czy_koniec() == "koniec")
			{
				wynik.wyznaczWygranego(&server_score, wygral);
				window->setMouseCursorVisible(true);
				return "GAME_OVER_MULTI";
			}

			int recive, sent;
			sent = 69;
			sendPacket << sent;
			while (flag)
			{
				window->clear();
				server.setPosition(200, 430);
				client.setPosition(1400, 430);
				plansza.rysuj(window);
				krazek.rysuj(window);
				server.rysuj(window);
				client.rysuj(window);
				window->draw(mojBaton("Waiting for server to connect"));
				window->display();

				socket.send(sendPacket, ipAddress, portServer);
				socket.receive(receivePacket, ipAddress, portServer);
				if (receivePacket >> recive && recive == 69)
				{
					flag = false;
					receivePacket.clear();
					sendPacket.clear();
				}
			}

			socket.receive(sendPacket, ipAddress, portClient);
			while (sendPacket >> mouseMoveX >> mouseMoveY && sendPacket != NULL)
			{
				server.move(Vector2f(mouseMoveX, mouseMoveY));
				sendPacket.clear();
			}

			client.move(Vector2f(eventSF.mouseMove.x, eventSF.mouseMove.y));
			receivePacket << eventSF.mouseMove.x << eventSF.mouseMove.y;
			socket.send(receivePacket, ipAddress, portClient);
			receivePacket.clear();

			if (Kolizje::sprawdzKolizje(&client.getShape(), &krazek.zwroc()))
			{
				krazek.setPredkosc(Kolizje::wyznaczPredkosc(&client.getShape(), &krazek.zwroc()));
			}
			else if (Kolizje::sprawdzKolizje(&server.getShape(), &krazek.zwroc()))
			{
				krazek.setPredkosc(Kolizje::wyznaczPredkosc(&server.getShape(), &krazek.zwroc()));
			}
		}

		int sprawdz = plansza.czyWplanszy(&krazek);

		if (sprawdz == 1)
		{
			wynik.SetScore(0);	// klient
		}
		else if (sprawdz == 2) 
		{
			wynik.SetScore(1); // serwer
		}
		else
		{
			krazek.move();
		}

		//while (accumulator > ups)
		//{
			//accumulator -= ups;
			window->clear();
			plansza.rysuj(window);
			krazek.rysuj(window);
			server.rysuj(window);
			client.rysuj(window);
			wynik.rysuj(window);
			window->display();
		//}
		//accumulator += clock.restart();
	}

	return "GAME_OVER_MULTI";
}

