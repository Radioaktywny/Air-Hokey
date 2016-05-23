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
<<<<<<< HEAD
	enum MenuState { MENU, MENU2, GAME_SINGLE, GAME_MULTI, SERVER, CLIENT, GAME_OVER, END };
=======
	enum MenuState { MENU, GAME_SINGLE, GAME_MULTI, GAME_OVER, END ,};
>>>>>>> origin/Marcin
	MenuState state;

private:
	Font font;
	void Singleplayer();
<<<<<<< HEAD
	void Multiplayer();
	void menus();
	void menusMulti();
=======
	void menus();
>>>>>>> origin/Marcin
};