#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#pragma once
using namespace::std;
using namespace::sf;
class Multiplayer
{
public:
	Multiplayer(sf::RenderWindow * window, sf::Font *font, std::string *wygral, std::string state);
	~Multiplayer();
	string eventsManage(sf::RenderWindow * window, sf::Event eventSF);
	Text mojBaton(string text);
	void threadServer();
	void threadClient();
	string run();
private:
	RenderWindow * window;
	Font *font;
	Event eventSF;
	string *wygral;
	string state;
	Clock clock;
	IpAddress ipAddress;
	UdpSocket socket;
	int mouseMoveServerX = 200;
	int mouseMoveServerY = 430;
	int mouseMoveClientX = 1400;
	int mouseMoveClientY = 430;
	Packet packet, receivePacket, sendPacket;
	unsigned short portServer = 54321;
	unsigned short portClient = 54322;
	bool isConnected = false;
};

