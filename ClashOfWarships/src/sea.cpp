#include "sea.hpp"

Sea::Tile::Tile(int positionX, int positionY, const sf::Texture& texture) : visual(sf::Sprite(texture)) {
	visual.setColor(sf::Color(status));
	visual.setPosition(positionX, positionY);
}

void Sea::Tile::setStatus(TileStatus newStatus) {
	status = newStatus;
	visual.setColor(sf::Color(newStatus));
}

Sea::Sea(int positionX, int positionY, const Resources& res) : positionX(positionX), positionY(positionY) {
	for (int i = 0; i < SEA_HEIGHT; i++) {
		for (int j = 0; j < SEA_WIDTH; j++) {
			map[i][j] = Tile(positionX + (j * SEA_TILE_SIZE), positionY + (i * SEA_TILE_SIZE), res.getTile());
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
	if (x >= positionX && x <= positionX + (SEA_TILE_SIZE * SEA_WIDTH) && y >= positionY && y <= positionY + (SEA_TILE_SIZE * SEA_HEIGHT)) {
		tileX = (x - positionX) / SEA_TILE_SIZE;
		tileY = (y - positionY) / SEA_TILE_SIZE;
		return map[tileY][tileX].getStatus() == Tile::untouched;
	}
	else return false;
}

AlliedSea::Ship::Ship(int positionTileX, int positionTileY, int sizeTileX, int sizeTileY, int seaPositionX, int seaPositionY, const sf::Texture& texture)
: positionTileX(positionTileX), positionTileY(positionTileY), sizeTileX(sizeTileX), sizeTileY(sizeTileY), seaPositionX(seaPositionX), seaPositionY(seaPositionY) {
	visual = sf::Sprite(texture);
	visual.setPosition(seaPositionX + (positionTileX * SEA_TILE_SIZE), seaPositionY + (positionTileY * SEA_TILE_SIZE));
}

AlliedSea::AlliedSea(int positionX, int positionY, const Resources& res) : Sea(positionX, positionY, res) {
	fleet[0] = Ship(0, 0, 4, 2, positionX, positionY, res.getCarrier());
	fleet[1] = Ship(0, 3, 4, 1, positionX, positionY, res.getBattleship());
	fleet[2] = Ship(0, 5, 3, 1, positionX, positionY, res.getCruiser());
	fleet[3] = Ship(0, 7, 2, 1, positionX, positionY, res.getDestroyer());
	fleet[4] = Ship(0, 9, 2, 1, positionX, positionY, res.getDestroyer());
	fleet[5] = Ship(2, 8, 1, 1, positionX, positionY, res.getSubmarine());
}

void AlliedSea::draw(sf::RenderWindow& window) {
	Sea::draw(window);
	for (int i = 0; i < SHIPS_COUNT; i++) {
		fleet[i].draw(window);
	}
}
