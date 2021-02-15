#include <SFML/Graphics.hpp>
#include "sea.hpp"
#include "resources.hpp"

int main()
{
	Resources res; // TODO: error window
	sf::Sprite background(res.getBackground()); // TODO: change color for efects
	sf::RenderWindow window(sf::VideoMode(960, 640), "Clash of Warships", sf::Style::Titlebar | sf::Style::Close);

	AlliedSea* s = new AlliedSea(40, 80, res); //for debug
	EnemySea* t = new EnemySea(520, 80, res); //for debug

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) { //for debug
				int x, y;
				bool aux = t->isActivePosition(event.mouseButton.x, event.mouseButton.y, x, y);
				if (aux) t->setMissed(x, y);
			}
		}
		window.clear();
		window.draw(background);

		s->draw(window); //for debug
		t->draw(window); //for debug

		window.display();
	}
}
