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
	int heldShip = -1;
	bool ok = true;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			int x, y;
			if (event.type == sf::Event::Closed) window.close();
			else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) { //for debug
				if (s->isActivePosition(event.mouseButton.x, event.mouseButton.y, x, y)) {
					if (heldShip == -1) heldShip = s->getShipIdOnPosition(x, y);
					else if (ok) heldShip = -1;
				}				
			}
			else if (event.type == sf::Event::MouseMoved && heldShip != -1 && s->isActivePosition(event.mouseMove.x, event.mouseMove.y, x, y)) {
				ok = s->setShipsPosition(heldShip, x, y);
			}
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right && s->isActivePosition(event.mouseButton.x, event.mouseButton.y, x, y)) {
				if (heldShip != -1) {
					ok = s->rotateShip(heldShip);
				}
			}
		}
		window.clear();
		window.draw(background);

		s->draw(window); //for debug
		t->draw(window); //for debug

		window.display();
	}
}
