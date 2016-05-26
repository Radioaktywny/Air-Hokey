#include "Kolizje.h"
#include<SFML/Graphics.hpp>


sf::Vector2f Kolizje::wyznaczPredkosc(sf::CircleShape* gracz, sf::CircleShape* krazek)
{
	
	//sf::Vector2f tmp(((gracz->getPosition().x + (gracz->getRadius())) - (krazek->getPosition().x + (krazek->getRadius()))), ((gracz->getPosition().y + (gracz->getRadius())) - (krazek->getPosition().y + (krazek->getRadius()))));
	//tmp.x = tmp.x / (tmp.x + tmp.y);
	//tmp.y = tmp.y / (tmp.x + tmp.y);
	//std::cout  << tmp.x << " : " << tmp.y <<"\n";
	sf::Vector2f tmp(0.001f, 0.001f);
	//wylicz prosta z 2 punktow
	int speed=10;
	int tab_kierunku[2];
	float xk = krazek->getPosition().x;
	float yk = krazek->getPosition().y;
	float xg = gracz->getPosition().x;
	float yg = gracz->getPosition().y;
	float a = (yk - yg) / (xk - xg);
	float b = (yk) / (xk*a);
	float xs;//szukana na x
	float ys;//szukana na y
	xs = xk - xg;
	if (xs < 0)
	{
		xs = xs*(-1);
	}	
	xs *= speed;//tu mial byc speed ale cos nie smiga XD
	ys = (a*xs + b);//prosta z x0 krazkow 
	//nadaj kierunek w innej metodzie powinno byc:
	if (krazek->getPosition().x > gracz->getPosition().x)//prawa
	{
		
			tab_kierunku[0] = 1;
			tab_kierunku[1] = 1;
	}
	else//lewa
	{
	
			tab_kierunku[0] = -1;
			tab_kierunku[1] = -1;
	}
	//std::cout << "x: " << tab_kierunku[0] << " : " << tab_kierunku[1] << " :y" << std::endl;
	tmp.x = xs*tab_kierunku[0];
	tmp.y = ys*tab_kierunku[1];


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





