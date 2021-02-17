#include <SFML/Graphics.hpp>
#include "sea.hpp"
#include "game.hpp"
#include "resources.hpp"

int main()
{
	// TODO: error window
	sf::Sprite background(Resources::getBackground()); // TODO: change color for efects
	sf::RenderWindow window(sf::VideoMode(960, 640), "Clash of Warships", sf::Style::Titlebar | sf::Style::Close);
	Game* g = new Game;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			else g->acceptEvent(event);
		}
		window.clear();
		window.draw(background);
		g->draw(window);
		window.display();
	}
	delete g;
}
