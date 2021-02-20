#include "game.hpp"

Game::Game() {
	allyHealth = alsea.getFleetsHealth();
	enemyHealth = allyHealth;
}

void Game::acceptEvent(const sf::Event& event) {
	if (status == preparation) processEventInPrep(event);
	else if (status == myTurn) processMyTurn(event);
}

void Game::processEventInPrep(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			int x, y;
			if (alsea.isActivePosition(event.mouseButton.x, event.mouseButton.y, x, y)) {
				if (heldShip == -1) heldShip = alsea.getShipIdOnPosition(x, y);
				else if (shipWellPlaced) heldShip = -1;
			}
		}
		if (event.mouseButton.button == sf::Mouse::Right) {
			int x, y;
			if (alsea.isActivePosition(event.mouseButton.x, event.mouseButton.y, x, y)) {
				if (heldShip != -1) shipWellPlaced = alsea.rotateShip(heldShip);
			}
		}
	}
	if (event.type == sf::Event::MouseMoved) {
		if (heldShip != -1) {
			int x, y;
			if (alsea.isActivePosition(event.mouseMove.x, event.mouseMove.y, x, y)) {
				shipWellPlaced = alsea.setShipsPosition(heldShip, x, y);
			}
		}
	}
}

bool Game::setReady() {
	if (heldShip == -1) {
		status = ready;
		return true;
	}
	else if (shipWellPlaced) {
		heldShip = -1;
		status = ready;
		return true;
	}
	else return false;
}

void Game::gaming(bool istart) {
	if (istart) status = myTurn;
	else status = hisTurn;
}

void Game::processMyTurn(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
		int x, y;
		if (ensea.isActivePosition(event.mouseButton.x, event.mouseButton.y, x, y)) {
			firedX = x;
			firedY = y;
			fired = true;
		}
	}
}

void Game::acceptImpact(bool hit) {
	if (hit) {
		ensea.setHit(firedX, firedY);
		enemyHealth--;
	}
	else ensea.setMissed(firedX, firedY);
}

bool Game::reportImpact(int x, int y) {
	if (alsea.getShipIdOnPosition(x, y) == -1) {
		alsea.setMissed(x, y);
		return false;
	} 
	else {
		alsea.setHit(x, y);
		allyHealth--;
		return true;
	}
}
