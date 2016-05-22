#pragma once
#include<SFML/Graphics.hpp>
class Kolizje
{
public:
	static sf::Vector2f wyznaczPredkosc(sf::CircleShape *gracz, sf::CircleShape *krazek);
	static bool sprawdzKolizje(sf::CircleShape *gracz, sf::CircleShape *krazek);
};

