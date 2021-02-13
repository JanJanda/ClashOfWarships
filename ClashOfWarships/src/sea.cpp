#include "sea.hpp"

Tile::Tile(int positionX, int positionY, const sf::Texture& texture) : visual(sf::Sprite(texture)) {
	visual.setColor(sf::Color(status));
	visual.setPosition(positionX, positionY);
}

void Tile::setStatus(tileStatus newStatus) {
	status = newStatus;
	visual.setColor(sf::Color(newStatus));
}

Sea::Sea(int positionX, int positionY) : positionX(positionX), positionY(positionY) {
	if (!tileTexture.loadFromFile("tile.jpg")) return; // TODO: error window
	for (int i = 0; i < seaHeight; i++) {
		for (int j = 0; j < seaWidth; j++) {
			map[i][j] = Tile(positionX + (j * seaTileSize), positionY + (i * seaTileSize), tileTexture);
		}
	}
}

void Sea::draw(sf::RenderWindow& window) {
	for (int i = 0; i < seaHeight; i++) {
		for (int j = 0; j < seaWidth; j++) {
			map[i][j].draw(window);
		}
	}
}
