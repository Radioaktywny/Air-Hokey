#include "UDP.h"
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

UDP::UDP()
{

}


UDP::~UDP()
{

}

void UDP::beServer()
{
		IpAddress ip = IpAddress::getLocalAddress();	// 192.168.0.103
		UdpSocket socket;
		char connectionType;
		char buffer[200];
		size_t received;
		int count_connections = 0;
		unsigned short port;
		map<unsigned short, IpAddress> computerID;
		string text = "Connected to:";
		
		cout << "Set port number: ";
		cin >> port;

		socket.bind(port);

		if (connectionType == 's')
		{
			IpAddress rIp;
			unsigned short port;
			socket.receive(buffer, sizeof(buffer), received, rIp, port);
			cout << 1;
			if (received > 0)
			{
				cout << 2;
				computerID[port] = rIp;
				cout << computerID[port];
			}
			cout << 3;
		}

		bool done = false;

		while (!done)
		{
				cout << 4;
				getline(cin, text);
				map<unsigned short, IpAddress>::iterator tempIterator;

				for (tempIterator = computerID.begin(); tempIterator != computerID.end(); tempIterator++)
				{
					socket.send(text.c_str(), text.length() + 1, tempIterator->second, tempIterator->first);
				}
		}
}

void UDP::beClient()
{
	IpAddress ip = IpAddress::getLocalAddress();	// 192.168.0.103
	UdpSocket socket;
	char buffer[200];
	size_t received;
	int count_connections = 0;
	unsigned short port;
	map<unsigned short, IpAddress> computerID;
	string text = "Connected to:";

	cout << 1;
	string sIp;
	cout << "Enter server ip:";
	char c;

	while (true)
	{

		c = (char)getch();
		if (c == 13)
		{
			break;
		}
		sIp += c;
		cout << "*";

	}
	cout << 2;
	IpAddress sendIP(sIp);
	socket.send(text.c_str(), text.length() + 1, sendIP, 2000);
	cout << 3;

	bool done = false;

	while (!done)
	{
		count_connections++;
		IpAddress tempIp;
		unsigned short tempPort;
		socket.receive(buffer, sizeof(buffer), received, tempIp, tempPort);
		if (received > 0)
		{
			cout << 4;
			if (count_connections == 1)
			{
				cout << "Connected";
			}
			else
				cout << "Received " << buffer << endl;

		}

		map<unsigned short, IpAddress>::iterator tempIterator;

		for (tempIterator = computerID.begin(); tempIterator != computerID.end(); tempIterator++)
		{
			socket.send(text.c_str(), text.length() + 1, tempIterator->second, tempIterator->first);
		}
	}
}
