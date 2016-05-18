
#include<SFML/Graphics.hpp>
class Bot
{
public:
	Bot();
	~Bot();
	void move(sf::Vector2f dir);
	void rysuj(sf::RenderWindow * window);
	sf::Vector2f getKierunek();
	sf::CircleShape* getShape();

private:
	sf::CircleShape krazek;
	sf::Vector2f kierunek;
};
