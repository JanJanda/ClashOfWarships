#include <SFML/Graphics.hpp>
#include "resources.hpp"
#include "button.hpp"
#include "game.hpp"

int main()
{
	// TODO: error window a napoveda
	sf::Sprite background(Resources::getBackground()); // TODO: change color for efects
	sf::RenderWindow window(sf::VideoMode(960, 640), "Clash of Warships", sf::Style::Titlebar | sf::Style::Close);
	Game* game = new Game;
	Button readyButton(320, 560, "READY");
	Button joinButton(520, 560, "JOIN");
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			else {
				game->acceptEvent(event);
				if (readyButton.isClicked(event)) background.setColor(sf::Color::Red); // for debug
				if (joinButton.isClicked(event)) background.setColor(sf::Color::White); // for debug
			}
		}
		window.clear();
		window.draw(background);
		game->draw(window);
		readyButton.draw(window);
		joinButton.draw(window);
		window.display();
	}
	delete game;
}
