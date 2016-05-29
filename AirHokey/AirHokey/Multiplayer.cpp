#include "Multiplayer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
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



Multiplayer::Multiplayer()
{
}



Multiplayer::~Multiplayer()
{
}



string Multiplayer::run(sf::RenderWindow * window, sf::Font *font, std::string *wygral, std::string state)
{
	
	window->setMouseCursorVisible(false);
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
	int mouseMoveX;
	int mouseMoveY;
	bool flag = true;
	bool bind = false;
	sf::Event eventSF;

	while (true)
	{
		while (window->pollEvent(eventSF))
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
				}
				break;
			case Event::MouseMoved:
				break;
			}
		}

		if (state == "SERVER")
		{
			if (!bind)
			{
				socket.bind(portServer);
				bind = true;
				std::cout << "binduje";
			}
			string recive, sent;
			sent = "hello client";

			while (flag)
			{
				socket.receive(receivePacket, ipAddress, portClient); // autobind adresu clienta
				if (receivePacket >> recive && recive == "hello server")
				{
					flag = false;
					sendPacket << sent;
					socket.send(sendPacket, ipAddress, portClient);
					receivePacket.clear();
					sendPacket.clear();
					std::cout << "styklo";
				}
			}

			std::cout << "stacja 1" << endl;

			server.move(Vector2f(eventSF.mouseMove.x, eventSF.mouseMove.y));
			sendPacket << eventSF.mouseMove.x << eventSF.mouseMove.y;
			socket.send(sendPacket, ipAddress, portClient);
			sendPacket.clear();

			socket.receive(receivePacket, ipAddress, portClient);
			while ((receivePacket >> mouseMoveX >> mouseMoveY && receivePacket != NULL))
			{
				client.move(Vector2f(mouseMoveX, mouseMoveY));
				std::cout << "stacja 2" << endl;
				receivePacket.clear();
			}

			std::cout << "stacja 3" << endl;

			if (Kolizje::sprawdzKolizje(&server.getShape(), &krazek.zwroc()))
			{
				Vector2f odbicie = Kolizje::wyznaczPredkosc(&server.getShape(), &krazek.zwroc());
				krazek.setPredkosc(odbicie);
			}
		}

		else
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

			cout << "stacja 1" << endl;
			socket.receive(sendPacket, ipAddress, portClient);
			while (sendPacket >> mouseMoveX >> mouseMoveY && sendPacket != NULL)
			{
				server.move(Vector2f(mouseMoveX, mouseMoveY));
				cout << "stacja 2" << endl;
				sendPacket.clear();
			}
			cout << "stacja 3" << endl;

			client.move(Vector2f(eventSF.mouseMove.x, eventSF.mouseMove.y));
			receivePacket << eventSF.mouseMove.x << eventSF.mouseMove.y;
			socket.send(receivePacket, ipAddress, portClient);
			receivePacket.clear();
			cout << "stacja 4" << endl;
			if (Kolizje::sprawdzKolizje(&client.getShape(), &krazek.zwroc()))
			{
				Vector2f odbicie = Kolizje::wyznaczPredkosc(&client.getShape(), &krazek.zwroc());
				krazek.setPredkosc(odbicie);
			}
		}

		krazek.move();
		plansza.czyWplanszy(&krazek);
		while (accumulator > ups)
		{
			accumulator -= ups;
			window->clear();
			plansza.rysuj(window);
			krazek.rysuj(window);
			server.rysuj(window);
			client.rysuj(window);
			window->display();
		}
		accumulator += clock.restart();
	}

	return "GAME_OVER";
}

