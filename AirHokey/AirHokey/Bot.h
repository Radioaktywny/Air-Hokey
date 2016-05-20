
#include<SFML/Graphics.hpp>
#include "Plansza.h"
class Bot
{
public:
	Bot(std::string polowa , Plansza * plansza , Krazek * Pilka);
	~Bot();
	void move();
	void rysuj(sf::RenderWindow * window);
	sf::Vector2f getKierunek();
	sf::CircleShape getShape();
	sf::CircleShape krazek;
private:
	std::string polowa;
	Krazek * pilka;
	void move_right_side();
	void move_left_side();
	float speed_do_lini = 0.4f;
	float speed_do_krazka = 0.4f;
	int linia_przy_bramce = 100;//powinienem ja wyznaczac !
	//int wymiary[2];//wymiary planszy /0:szerokosc /1:wysokosc
	//sf::CircleShape krazek;
	Plansza *plansza;
	sf::Vector2f kierunek;
};
