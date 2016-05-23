#include <SFML/Graphics.hpp>
#include <Windows.h>
#include<string>
#include<iostream>
#include "Plansza.h"
#include "Gracz.h"
#include "Krazek.h"

using namespace std;
using namespace sf;

class Menu
{
public:
	Menu(void);
	~Menu(void);

	void runMenu();

protected:
	enum MenuState { MENU, MENU2, GAME_SINGLE, GAME_MULTI, SERVER, CLIENT, GAME_OVER, END };
	MenuState state;

private:
	Font font;
	void Singleplayer();
	void Multiplayer();
	void menus();
	void menusMulti();
};