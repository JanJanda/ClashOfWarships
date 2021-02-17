#include "game.hpp"

void Game::acceptEvent(const sf::Event& event) {
	if (status == preparation) processEventInPrep(event);
}

void Game::processEventInPrep(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			int x, y;
			if (alsea.isActivePosition(event.mouseButton.x, event.mouseButton.y, x, y)) {
				if (heldShip == -1) heldShip = alsea.getShipIdOnPosition(x, y);
				else if (shipPlaced) heldShip = -1;
			}
		}
		if (event.mouseButton.button == sf::Mouse::Right) {
			int x, y;
			if (alsea.isActivePosition(event.mouseButton.x, event.mouseButton.y, x, y)) {
				if (heldShip != -1) shipPlaced = alsea.rotateShip(heldShip);
			}
		}
	}
	if (event.type == sf::Event::MouseMoved) {
		if (heldShip != -1) {
			int x, y;
			if (alsea.isActivePosition(event.mouseMove.x, event.mouseMove.y, x, y)) {
				shipPlaced = alsea.setShipsPosition(heldShip, x, y);
			}
		}
	}
}
