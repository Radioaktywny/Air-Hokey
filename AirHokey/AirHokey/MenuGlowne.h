#pragma once
#include<SFML/Graphics.hpp>
#include <string>
class MenuGlowne
{
public:
	MenuGlowne();
	~MenuGlowne();
	std::string run(sf::RenderWindow * window, sf::Font *font);
};

