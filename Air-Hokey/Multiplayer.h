#include <SFML/Graphics.hpp>

#pragma once
using namespace::std;
using namespace::sf;
class Multiplayer
{
public:
	Multiplayer();
	~Multiplayer();
	void eventsManage(sf::RenderWindow * window, sf::Event eventSF);
	sf::Text mojBaton(string text, sf::Font *font);
	void funkcja();
	string run(sf::RenderWindow * window, sf::Font * font, std::string * wygral, std::string state);
};

