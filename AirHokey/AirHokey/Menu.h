#include <SFML/Graphics.hpp>
#include <Windows.h>
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
	enum MenuState { MENU, GAME_SINGLE, GAME_MULTI, GAME_OVER, END , CONN_MULTI, SERVER, CLIENT, };
	MenuState state;

private:
	Font font;
	string wygral;
	void singleplayer();
	void menuGlowne();
	void menuKoniecGry();
	void menuPolaczenieMulti();
	void state_update(String bedzie);
	void multiplayerServer();
	void multiplayerClient();
};