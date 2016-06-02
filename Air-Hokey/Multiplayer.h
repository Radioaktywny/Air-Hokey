#include <SFML/Graphics.hpp>

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
	string funkcja(int pyk);
	string run();
private:
	RenderWindow * window;
	Font *font;
	Event eventSF;
	string *wygral;
	string state;
};

