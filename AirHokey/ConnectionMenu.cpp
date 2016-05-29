#include "ConnectionMenu.h"
#include <SFML/Graphics.hpp>



ConnectionMenu::ConnectionMenu()
{
}


ConnectionMenu::~ConnectionMenu()
{
}

std::string ConnectionMenu::run(sf::RenderWindow *window, sf::Font * font)
{
	sf::Text title("RODZAJ POLACZENIA", *font, 80);//tytu³
	title.setStyle(sf::Text::Bold);
	title.setPosition(1600 / 2 - title.getGlobalBounds().width / 2, 20);
	const int ile = 4;
	sf::Text tekst[ile]; // teksty przycisków
	std::string str[] = { "Server", "Client" , "Back to Menu" ,"Exit" };
	for (int i = 0; i < ile; i++)
	{
		tekst[i].setFont(*font);
		tekst[i].setCharacterSize(65);
		tekst[i].setString(str[i]);
		tekst[i].setPosition(1600 / 2 - tekst[i].getGlobalBounds().width / 2, 250 + i * 120);
	}

	while (true)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(*window));
		sf::Event event;

		while (window->pollEvent(event))
		{
			//Wciœniêcie ESC 
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Escape) return "END";
			//bedzie tworzyl server
			else if (tekst[0].getGlobalBounds().contains(mouse) &&
				event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				return "SERVER";
			}
			//bedzie dolaczal
			else if (tekst[1].getGlobalBounds().contains(mouse) &&
				event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{;
				return "CLIENT";
			}
			//powrot do glownego
			else if (tekst[2].getGlobalBounds().contains(mouse) &&
				event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				//state = END;
				return "MENU";
			}
			//klikniêcie Exit
			else if (tekst[3].getGlobalBounds().contains(mouse) &&
				event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				return "END";
			}
		}

		//kolory jak najedziesz
		for (int i = 0; i < ile; i++)
			if (tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setColor(sf::Color::Red);
			else tekst[i].setColor(sf::Color::White);

			window->clear();

			window->draw(title);
			for (int i = 0; i < ile; i++)
				window->draw(tekst[i]);
			window->display();
	}
}