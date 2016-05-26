#include<SFML/Graphics.hpp>
#include "Score.h"
#include<string>

Score::Score(sf::Font * font)
{	
	this->prawa = 0;
	this->lewa = 0;
	//this->font = font;
	const int ile = 3;
	
	//this->tekst[ile]; // teksty przycisków
	std::string str[] = { "0" , ":","0", };
	for (int i = 0; i < ile; i++)
	{
		this->tekst[i].setFont(*font);
		this->tekst[i].setCharacterSize(65);
		this->tekst[i].setString(str[i]);
		if (i == 0)
			this->tekst[i].setPosition(1600 / 2 - 50, 40);//lewa
		if (i == 1)
			this->tekst[i].setPosition(1600 / 2, 40);//             :
		if (i == 2)
			this->tekst[i].setPosition(1600 / 2 + 50, 40);//			prawa
			this->tekst[i].setColor(sf::Color::White);
	}
}


Score::~Score()
{
}



void Score::SetScore(int i)
{	
	if (i == 0)
	{
		lewa=lewa+1;
		
	}
	else
	{
		prawa=prawa+1;
	}
	tekst[0].setString(std::to_string(lewa));
	tekst[2].setString(std::to_string(prawa));
}

void Score::rysuj(sf::RenderWindow * window)
{
	for(int i = 0; i < this->ile; i++)
	window->draw(this->tekst[i]);
}
