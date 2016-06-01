#include<SFML/Graphics.hpp>
#include "Score.h"
#include<string>
#include <Windows.h>
#include <iostream>

#define MessageBoxA
Score::Score(sf::Font * font)
{	
	this->prawa = 0;
	this->lewa = 0;
	//this->font = font;
	const int ile = 3;
	laduj_goal();
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
	
		prawa++;
	}
	else
	{
		lewa++;	
	}
	tekst[0].setString(std::to_string(lewa));
	tekst[2].setString(std::to_string(prawa));
	this->jest_bramka = true;
	
}

void Score::rysuj(sf::RenderWindow * window)
{	
	for(int i = 0; i < this->ile; i++)
	window->draw(this->tekst[i]);
	if (this->jest_bramka)
	{
		window->draw(this->sprite_goal);
		window->display();
		jest_bramka = false;
		Sleep(this->czas_po_golu);
	}
}

std::string Score::kto_wygral()
{
	if(this->lewa < this->prawa)
	return "lewa";
	if (this->lewa > this->prawa)
	return "prawa";
}

void Score::wyznaczWygranego(std::string * bot_strona, std::string * wygral)
{
	if (*bot_strona == kto_wygral())
	{
		*wygral = "WYGRALES :)";
	}
	else
	{
		*wygral = "PRZEGRALES :(";
	}
}

void Score::laduj_goal()
{

	if (!image.loadFromFile("data/goal.png"))
	{
		MessageBoxA(NULL, "Nie ma pliku z golem!", "ERROR", NULL);
		return;
	}
	this->sprite_goal.setTexture(image);
	this->sprite_goal.setPosition(1100 / 2, 600 / 2);
}

std::string Score::czy_koniec()
{
	//std::cout << lewa <<":"<< koniec_gry << std::endl;
	if (this->lewa == this->koniec_gry)
	{

		return "koniec";
	}
	if (this->prawa == this->koniec_gry)
	{
		return "koniec";
	}
	return "";
}
