#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Game_manager.h"

using namespace std;
using namespace sf;

int main()
{
	Game_manager manager;
	manager.init_blocks();
	while (manager.window.isOpen())
	{
		sf::Event event;

		manager.window.pollEvent(event);
		if (event.type == sf::Event::Closed)
			manager.window.close();

		manager.window.clear();

		switch (manager.state)
		{
		case CONTINUE:
			manager.update();
			manager.draw_field();
			break;

		case OVER:
			manager.window.clear(sf::Color::White);
			manager.init_blocks();

			if (Keyboard::isKeyPressed(Keyboard::Key::Space))
			{
				manager.state = STATES::CONTINUE;
				sleep(milliseconds(150));
			}
			manager.window.clear(sf::Color::White);
			sleep(seconds(0.8f));
			manager.state = STATES::CONTINUE;
			break;
		}
	}

	return 0;
}