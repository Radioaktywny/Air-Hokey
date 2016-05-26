#pragma once
class Score
{
public:
	Score();
	Score(sf::Font * font);
	~Score();
	void SetScore(int i);
	void rysuj(sf::RenderWindow * window);
private:
	int Score::prawa;
	int Score::lewa;
	const int ile = 3;
	sf::Text tekst[3];
};

