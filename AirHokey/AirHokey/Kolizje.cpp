#include "Kolizje.h"
#include<SFML/Graphics.hpp>
#include <iostream>
sf::Vector2f Kolizje::wyznaczPredkosc(sf::CircleShape* gracz, sf::CircleShape* krazek)
{
	
	sf::Vector2f tmp(((gracz->getPosition().x + (gracz->getRadius())) - (krazek->getPosition().x + (krazek->getRadius()))), ((gracz->getPosition().y + (gracz->getRadius())) - (krazek->getPosition().y + (krazek->getRadius()))));
	tmp.x = tmp.x / (tmp.x + tmp.y);
	tmp.y = tmp.y / (tmp.x + tmp.y);
	//std::cout  << tmp.x << " : " << tmp.y <<"\n";
	return tmp;
}

bool Kolizje::sprawdzKolizje(sf::CircleShape* gracz, sf::CircleShape* krazek)
{
	sf::Vector2f tmp(((gracz->getPosition().x+(gracz->getRadius())) - (krazek->getPosition().x+(krazek->getRadius()))), ((gracz->getPosition().y + (gracz->getRadius())) - (krazek->getPosition().y +( krazek->getRadius()))));
	if (sqrtf((tmp.x*tmp.x) + (tmp.y*tmp.y)) <= (gracz->getRadius() + krazek->getRadius()))
		return true;
	else
		return false;
}
