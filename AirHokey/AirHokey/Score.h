#pragma once
#include<string>
class Score
{
public:
	Score();
	Score(sf::Font * font);
	~Score();
	void SetScore(int i);
	std::string czy_koniec();
	void rysuj(sf::RenderWindow * window);
	std::string kto_wygral();
private:
	int Score::prawa;
	int czas_po_golu = 500;
	bool jest_bramka = false;
	int Score::lewa;
	const int ile = 3;
	sf::Text tekst[3];
	sf::Sprite sprite_goal;
	void laduj_goal();
	sf::Texture image;
	int koniec_gry = 2;
};

