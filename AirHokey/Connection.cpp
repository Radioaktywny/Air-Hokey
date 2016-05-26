#include "Connection.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <cmath>
#include <thread>
#include <iostream>
#include <cstdlib>
#include <process.h>
#include <conio.h>
#include <map>
#include <string>
#pragma warning(disable:4996)

using namespace std;
using namespace sf;



Connection::Connection()
{
}


Connection::~Connection()
{

}

void Connection::isServer(CircleShape* gracz1, CircleShape* gracz2, CircleShape* krazek)
{

	IpAddress ipClient;
	UdpSocket socket;
	string text = "Connected to:";
	unsigned short portServer = 54321;
	unsigned short portClient = 54322;
	Packet packet, startPacket;
	Event event;

	socket.bind(portServer);
	Uint8 recived, sent;
	sent = 2;
	//Establishing connection

	bool flag = true;
	do
	{
		socket.receive(startPacket, ipClient, portClient);
		//dodac przypsanie adresu clienta/auto bind?
		if (startPacket >> recived && recived == 1)
		{
			flag = false;
			startPacket << sent;
			socket.send(startPacket, ipClient, portClient);
		}
	} while (flag);

	//Server side update

	Vector2f g1Position, g1Prev, g2Position, g2Prev, kPosition, kPrev;
	while (true) // do testow
	{
		g1Prev = gracz1->getPosition();
		g2Position = gracz2->getPosition();
		g2Prev = g2Position;
		kPosition = krazek->getPosition();
		kPrev = kPosition;
		socket.receive(packet, ipClient, portClient);
		if (packet >> g2Position.x >> g2Position.y >> kPosition.x >> kPosition.y)
		{
			//if (kPrevious != kPosition) krazek->move(kPosition);
			if (g2Prev != g2Position) gracz2->move(g2Position); //????? sprawdzic to czy move czy set
		}

		g1Position = Vector2f(event.mouseMove.x, event.mouseMove.y);
		if (g1Prev != g1Position) //ruch g1
		{
			packet << g1Position.x << g1Position.y << kPosition.x << kPosition.y;
			gracz1->move(g1Position);
			socket.send(packet, ipClient, portClient); // ktory port?
		}
	}
}
void Connection::isClient(CircleShape* gracz1, CircleShape* gracz2, CircleShape* krazek)
{

	IpAddress ipServer;
	UdpSocket socket;
	unsigned short portServer = 54321;
	unsigned short portClient = 54322;
	Packet packet, startPacket;
	Event event;

	cout << "Podaj ip servera" << endl;
	cin >> ipServer;
	socket.bind(portClient);
	Uint8 recived, sent;
	bool flag = true;
	do
	{
		sent = 1;
		socket.send(startPacket, ipServer, portServer);
		socket.receive(startPacket, ipServer, portServer);
		if (startPacket >> recived && recived == 2)
		{
			flag = false; //moze sie zmienic
						  //break;
		}
	} while (flag);

	Vector2f g1Position, g1Prev, g2Position, g2Prev, kPosition, kPrev;
	while (true) // do testu
	{
		g2Prev = gracz2->getPosition();
		g1Position = gracz1->getPosition();
		g1Prev = g1Position;
		kPosition = krazek->getPosition();
		kPrev = kPosition;
		socket.receive(packet, ipServer, portServer);
		if (packet >> g1Position.x >> g1Position.y >> kPosition.x >> kPosition.y)
		{
			//if (kPrevious != kPosition) krazek->move(kPosition);
			if (g1Prev != g1Position) gracz1->move(g1Position); //????? sprawdzic to czy move czy set
		}

		g2Position = Vector2f(event.mouseMove.x, event.mouseMove.y);
		if (g2Prev != g2Position) //ruch g1
		{
			packet << g2Position.x << g2Position.y << kPosition.x << kPosition.y;
			gracz1->move(g2Position);
			socket.send(packet, ipServer, portServer);
		}
	}


}