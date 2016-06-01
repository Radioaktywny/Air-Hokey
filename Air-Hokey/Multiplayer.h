#include <SFML/Graphics.hpp>
#pragma once
using namespace::std;
class Multiplayer
{
public:
	Multiplayer();
	~Multiplayer();
	string eventsManage(sf::RenderWindow * window, sf::Event eventSF);
	sf::Text mojBaton(string text, sf::Font *font);
	string funkcja();
	string run(sf::RenderWindow * window, sf::Font * font, std::string * wygral, std::string state);
};

