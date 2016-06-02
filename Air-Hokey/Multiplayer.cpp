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


using namespace sf;
using namespace std;

Multiplayer::Multiplayer(RenderWindow * window, Font *font, string *wygral, string state)
{
	this->window = window;
	this->font = font;
	this->wygral = wygral;
	this->state = state;
}

Multiplayer::~Multiplayer(){}

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

void Multiplayer::threadServer()
{
	cout << "uruchamiam wateczek";
	while (isConnected)
	{
		cout << "* ";
		this->sendPacket << mouseMoveServerX << mouseMoveServerY;
		this->socket.send(sendPacket, ipAddress, portClient);
		this->sendPacket.clear();
		socket.receive(receivePacket, ipAddress, portClient);
		while ((receivePacket >> mouseMoveClientX >> mouseMoveClientY && receivePacket != NULL))
		{
			this->mouseMoveClientX = mouseMoveClientX;
			this->mouseMoveClientY = mouseMoveClientY;
			this->receivePacket.clear();
		}
		this_thread::sleep_for(chrono::microseconds(8));
	}
}

void Multiplayer::threadClient()
{
	cout << "uruchamiam wateczek";
	while (isConnected)
	{
		cout << "* ";
		this->socket.receive(sendPacket, ipAddress, portClient);
		while (sendPacket >> mouseMoveServerX >> mouseMoveServerY && sendPacket != NULL)
		{
			this->mouseMoveServerX = mouseMoveServerX;
			this->mouseMoveServerY = mouseMoveServerY;
			this->sendPacket.clear();
		}
		this->receivePacket << mouseMoveClientX << mouseMoveClientY;
		this->socket.send(receivePacket, ipAddress, portClient);
		this->receivePacket.clear();
		this_thread::sleep_for(chrono::microseconds(8));
	}
}

string Multiplayer::run()
{
	this->window->setMouseCursorVisible(false);
	this->window->setFramerateLimit(120);
	this->ipAddress = IpAddress::getLocalAddress(); //"89.69.45.247";
	Score wynik(font);
	int szerokosc = 1500;
	int wysokosc = 600;
	Plansza plansza(sf::Vector2f(szerokosc, wysokosc), sf::Color(100, 200, 200));
	Gracz server;
	Gracz client(sf::Color::Magenta);
	Krazek krazek;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);
	sf::Vector2f myszka(0, 0);
	bool bind = false;
	bool flag = true;
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
				isConnected = false;
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

				this->socket.receive(receivePacket, ipAddress, portClient);
				if (receivePacket >> recive && recive == 69)
				{
					flag = false;
					isConnected = true;
					sendPacket << sent;
					this->socket.send(sendPacket, ipAddress, portClient);
					this->receivePacket.clear();
					this->sendPacket.clear();
					thread t1([=] {threadServer(); });
					t1.detach();
				}
			}

			mouseMoveServerX = eventSF.mouseMove.x;
			mouseMoveServerY = eventSF.mouseMove.y;
			server.move(Vector2f(mouseMoveServerX, mouseMoveServerY));
			client.move(Vector2f(mouseMoveClientX, mouseMoveClientY));

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
				isConnected = false;
				return "GAME_OVER_MULTI";
			}

			int recive, sent;
			sent = 69;
			sendPacket << sent;
			while (flag)
			{
				window->clear();
				//server.setPosition(200, 430);
			//	client.setPosition(1400, 430);
				plansza.rysuj(window);
				krazek.rysuj(window);
				server.rysuj(window);
				client.rysuj(window);
				window->draw(mojBaton("Waiting for server to connect"));
				window->display();
				////////////////////////////////////////////////////////
				this->socket.send(sendPacket, ipAddress, portServer);
				this->socket.receive(receivePacket, ipAddress, portServer);
				if (receivePacket >> recive && recive == 69)
				{																//JAKBYS TO TYLKO WSADZIL W WATEK BEZ ZADNEGO OKNA TYLKO JAKO COS CO ODBIERA TYLKO WSPOLRZEDNE
					flag = false;
					isConnected = true;
					this->receivePacket.clear();
					this->sendPacket.clear();
					thread t1([=] {threadClient(); });
					t1.detach();
				}
				//////////////////////////////////////////////////////
			}

			server.move(Vector2f(mouseMoveServerX, mouseMoveServerY));
			this->mouseMoveClientX = eventSF.mouseMove.x;
			this->mouseMoveClientY = eventSF.mouseMove.y;
			client.move(Vector2f(mouseMoveClientX, mouseMoveClientY));

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

		window->clear();
		plansza.rysuj(window);
		krazek.rysuj(window);
		server.rysuj(window);
		client.rysuj(window);
		wynik.rysuj(window);
		window->display();
	}
	return "GAME_OVER_MULTI";
}

