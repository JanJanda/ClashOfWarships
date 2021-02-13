#ifndef SEA_HPP
#define SEA_HPP

#include <SFML/Graphics.hpp>

const int seaTileSize = 40;
const int seaWidth = 10;
const int seaHeight = 10;

struct Tile {
	enum tileStatus : sf::Uint32 {
		untouched = 0xffffffff,
		gone = 0xffffff00
	};
	Tile() {};
	Tile(int positionX, int positionY, const sf::Texture& texture);
	void draw(sf::RenderWindow& window) { window.draw(visual); }
	tileStatus getStatus() { return status; }
	void setStatus(tileStatus newStatus);
private:
	tileStatus status{ Tile::untouched };
	sf::Sprite visual;
};

class Sea {
protected:
	sf::Texture tileTexture;
	Tile map[seaHeight][seaWidth];
	int positionX;
	int positionY;
public: // virual destrucktor?
	Sea(int positionX, int positionY);
	void draw(sf::RenderWindow& window);
};

#endif
