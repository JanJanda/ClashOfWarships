#include "sea.hpp"
#include "resources.hpp"

Sea::Tile::Tile(int positionX, int positionY) {
	visual.setColor(sf::Color(status));
	visual.setPosition(positionX, positionY);
}

void Sea::Tile::setStatus(TileStatus newStatus) {
	status = newStatus;
	visual.setColor(sf::Color(newStatus));
}

Sea::Sea(int positionX, int positionY) : positionX(positionX), positionY(positionY) {
	for (int i = 0; i < SEA_HEIGHT; i++) {
		for (int j = 0; j < SEA_WIDTH; j++) {
			map[i][j] = Tile(positionX + (j * SEA_TILE_SIZE), positionY + (i * SEA_TILE_SIZE));
		}
	}
}

void Sea::draw(sf::RenderWindow& window) {
	for (int i = 0; i < SEA_HEIGHT; i++) {
		for (int j = 0; j < SEA_WIDTH; j++) {
			map[i][j].draw(window);
		}
	}
}

bool Sea::isActivePosition(int x, int y, int& tileX, int& tileY) {
	if (x >= positionX && x < positionX + (SEA_TILE_SIZE * SEA_WIDTH) && y >= positionY && y < positionY + (SEA_TILE_SIZE * SEA_HEIGHT)) {
		tileX = (x - positionX) / SEA_TILE_SIZE;
		tileY = (y - positionY) / SEA_TILE_SIZE;
		return map[tileY][tileX].getStatus() == Tile::untouched;
	}
	else return false;
}

AlliedSea::Ship::Ship(int positionTileX, int positionTileY, int sizeTileX, int sizeTileY, int seaPositionX, int seaPositionY, const sf::Texture& texture)
: positionTileX(positionTileX), positionTileY(positionTileY), sizeTileX(sizeTileX), sizeTileY(sizeTileY), seaPositionX(seaPositionX), seaPositionY(seaPositionY), visual(texture), health(sizeTileX * sizeTileY) {
	visual.setPosition(seaPositionX + (positionTileX * SEA_TILE_SIZE), seaPositionY + (positionTileY * SEA_TILE_SIZE));
}

void AlliedSea::Ship::setPosition(int tileX, int tileY) {
	visual.setPosition(seaPositionX + (tileX * SEA_TILE_SIZE), seaPositionY + (tileY * SEA_TILE_SIZE));
	positionTileX = tileX;
	positionTileY = tileY;
}

void AlliedSea::Ship::rotate() {
	if (sizeTileX > sizeTileY) {
		visual.rotate(-90);
		visual.setOrigin(sizeTileX * SEA_TILE_SIZE, 0);
	}
	else if (sizeTileX < sizeTileY) {
		visual.rotate(90);
		visual.setOrigin(0, 0);
	}
	int tmp = sizeTileX;
	sizeTileX = sizeTileY;
	sizeTileY = tmp;
}

void AlliedSea::Ship::setMisplaced(bool a) {
	if (a) visual.setColor(sf::Color(0xff000080));
	else visual.setColor(sf::Color(0xffffffff));
	misplaced = a;
}

bool AlliedSea::Ship::covers(int tileX, int tileY) {
	return tileX >= positionTileX && tileX < positionTileX + sizeTileX && tileY >= positionTileY && tileY < positionTileY + sizeTileY;
}

AlliedSea::AlliedSea(int positionX, int positionY) : Sea(positionX, positionY) {
	fleet[0] = Ship(0, 0, 4, 2, positionX, positionY, Resources::getCarrier());
	fleet[1] = Ship(0, 3, 4, 1, positionX, positionY, Resources::getBattleship());
	fleet[2] = Ship(0, 5, 3, 1, positionX, positionY, Resources::getCruiser());
	fleet[3] = Ship(0, 7, 2, 1, positionX, positionY, Resources::getDestroyer());
	fleet[4] = Ship(0, 9, 2, 1, positionX, positionY, Resources::getDestroyer());
	fleet[5] = Ship(2, 8, 1, 1, positionX, positionY, Resources::getSubmarine());
}

void AlliedSea::draw(sf::RenderWindow& window) {
	Sea::draw(window);
	for (int i = 0; i < SHIPS_COUNT; i++) {
		fleet[i].draw(window);
	}
}

int AlliedSea::getShipIdOnPosition(int tileX, int tileY) {
	for (int i = 0; i < SHIPS_COUNT; i++) {
		if (fleet[i].covers(tileX, tileY)) return i;
	}
	return -1;
}

bool AlliedSea::setShipsPosition(int shipId, int tileX, int tileY) {
	fleet[shipId].setPosition(tileX, tileY);
	bool check = checkPlacement(shipId);
	fleet[shipId].setMisplaced(!check);
	return check;
}

bool AlliedSea::rotateShip(int shipId) {
	fleet[shipId].rotate();
	if (checkPlacement(shipId)) {
		fleet[shipId].setMisplaced(false);
		return true;
	}
	else {
		fleet[shipId].setMisplaced(true);
		return false;
	}
}

bool AlliedSea::checkPlacement(int shipId) {
	if (fleet[shipId].getPositionX() + fleet[shipId].getSizeX() > SEA_WIDTH || fleet[shipId].getPositionY() + fleet[shipId].getSizeY() > SEA_HEIGHT) {
		return false;
	}
	for (int i = 0; i < SHIPS_COUNT; i++) {
		if (i != shipId) {
			if (fleet[shipId].getPositionX() < fleet[i].getPositionX() + fleet[i].getSizeX() &&
				fleet[shipId].getPositionX() + fleet[shipId].getSizeX() > fleet[i].getPositionX() &&
				fleet[shipId].getPositionY() < fleet[i].getPositionY() + fleet[i].getSizeY() &&
				fleet[shipId].getPositionY() + fleet[shipId].getSizeY() > fleet[i].getPositionY()) {
				return false;
			}
		}
	}
	return true;
}

int AlliedSea::getFleetsHealth() {
	int tmp = 0;
	for (int i = 0; i < SHIPS_COUNT; i++) {
		tmp += fleet[i].getHealth();
	}
	return tmp;
}

void AlliedSea::setHit(int tileX, int tileY) {
	map[tileY][tileX].setStatus(Tile::hitAlly);
	int s = getShipIdOnPosition(tileX, tileY);
	if (s >= 0 && s < SHIPS_COUNT) fleet[s].reduceHealth();
}
