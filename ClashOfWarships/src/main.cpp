#include <SFML/Graphics.hpp>
#include "sea.hpp"

int main()
{
	sf::Texture bcgTexture;
	if (!bcgTexture.loadFromFile("background.jpg")) return 0; // TODO: error window
	sf::Sprite background(bcgTexture); // TODO: change color for efects
	sf::RenderWindow window(sf::VideoMode(960, 640), "Clash of Warships", sf::Style::Titlebar | sf::Style::Close);

	Sea* s = new Sea(40, 80);
	Sea* t = new Sea(520, 80);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}
		window.clear();
		window.draw(background);

		s->draw(window);
		t->draw(window);

		window.display();
	}
}
