
#include<SFML/Graphics.hpp>
#include "Plansza.h"
class Bot
{
public:
	Bot(std::string polowa , Plansza * plansza , Krazek * Pilka);
	~Bot();
	void move();
	void rysuj(sf::RenderWindow * window);
	void moveTo(float x , float y);
	sf::Vector2f getKierunek();
	sf::CircleShape getShape();
	sf::CircleShape krazek;
	void juzuderzylem();
	
private:
	std::string polowa;
	Krazek * pilka;
	void move_right_side();
	void move_left_side();
	float speed_do_lini = 2.5f;
	float speed_do_krazka = 2.5f;// 0.2f;<-poziom low xd / 0.4f <-poziom kozak xd
	int linia_przy_bramce = 100;//powinienem ja wyznaczac !
	//int wymiary[2];//wymiary planszy /0:szerokosc /1:wysokosc
	//sf::CircleShape krazek;
	Plansza *plansza;
	sf::Vector2f kierunek;
	bool uderzylem;
};
