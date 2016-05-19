
#include<SFML/Graphics.hpp>
#include <string.h>
#include <string>
class Bot
{
public:
	Bot(std::string polowa);
	~Bot();
	void move(sf::Vector2f dir);
	void rysuj(sf::RenderWindow * window);
	sf::Vector2f getKierunek();
	sf::CircleShape getShape();

private:
	std::string polowa;
	sf::CircleShape krazek;
	sf::Vector2f kierunek;
};
