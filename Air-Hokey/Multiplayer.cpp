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
#include <thread>
#include <future>




Multiplayer::Multiplayer()
{
}



Multiplayer::~Multiplayer()
{
}

void Multiplayer::eventsManage(sf::RenderWindow * window, sf::Event eventSF)
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
			//	return "MENU";
				window->close();
			}
			break;
		case Event::MouseMoved:
			break;
		}
	}
	//return "";
}

Text Multiplayer::mojBaton(string text, sf::Font *font)
{
	sf::Text clickStart(text, *font, 45);
	clickStart.setStyle(sf::Text::Bold);
	clickStart.setColor(Color::Black);
	clickStart.setPosition(1600 / 2 - clickStart.getGlobalBounds().width / 2, 200);
	return clickStart;
}

void Multiplayer::funkcja()
{
	//return "";
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
	int mouseMoveX, mouseMoveY;
	bool flag = true;
	bool bind = false;
	sf::Event eventSF;
	window->pollEvent(eventSF);

	while (true)
	{
		//if (eventsManage(window, eventSF) == "MENU")
		//	return "MENU";
			
		if (state == "SERVER")
		{
			if (!bind)
			{
				socket.bind(portServer);
				bind = true;
			}

			int recive, sent;
			sent = 69;

			while (flag)
			{
				//std::thread t1(&Multiplayer::eventsManage,window,eventSF);


				window->clear();
				server.setPosition(200, 430);
				client.setPosition(1400, 430);
				plansza.rysuj(window);
				krazek.rysuj(window);
				server.rysuj(window);
				client.rysuj(window);
				window->draw(mojBaton("Waiting for client to connect", font));
				window->display();
				//// tu musi byc wateczek
				socket.receive(receivePacket, ipAddress, portClient); // autobind adresu clienta
				if (receivePacket >> recive && recive == 69)
				{
					/*window->draw(mojBaton("Client connected. Click to start", font));
					window->display();*/
					
					flag = false;
					sendPacket << sent;
					socket.send(sendPacket, ipAddress, portClient);
					receivePacket.clear();
					sendPacket.clear();
					std::cout << "styklo";
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
				window->draw(mojBaton("Waiting for client to connect", font));
				window->display();

				socket.send(sendPacket, ipAddress, portServer);
				socket.receive(receivePacket, ipAddress, portServer);
				if (receivePacket >> recive && recive == 69)
				{
					flag = false;
					receivePacket.clear();
					sendPacket.clear();
					cout << "styklo";
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

