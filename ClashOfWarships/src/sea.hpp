#ifndef SEA_HPP
#define SEA_HPP

#include <SFML/Graphics.hpp>

const int SEA_TILE_SIZE = 40; // static?
const int SEA_WIDTH = 10;
const int SEA_HEIGHT = 10;
const int SHIPS_COUNT = 6;

class Sea {
protected:

	struct Tile {
		enum TileStatus : sf::Uint32 {
			untouched = 0xffffffff,
			missed = 0x0000ffff,
			hitEnemy = 0xff0000ff,
			hitAlly = 0x000000ff
		};
		Tile() {}
		Tile(int positionX, int positionY);
		void draw(sf::RenderWindow& window) { window.draw(visual); }
		TileStatus getStatus() { return status; }
		void setStatus(TileStatus newStatus);
	private:
		TileStatus status{ untouched };
		sf::Sprite visual;
	};

	Tile map[SEA_HEIGHT][SEA_WIDTH];
	const int positionX;
	const int positionY;
public: // virtual destrucktor?
	Sea(int positionX, int positionY);
	void draw(sf::RenderWindow& window);
	bool isActivePosition(int x, int y, int& tileX, int& tileY);
	void setMissed(int tileX, int tileY) { map[tileY][tileX].setStatus(Tile::missed); }
};

class EnemySea : public Sea { // je to potreba?
public:
	EnemySea(int positionX, int positionY) : Sea(positionX, positionY) {}
	void setHit(int tileX, int tileY) { map[tileY][tileX].setStatus(Tile::hitEnemy); }
};

class AlliedSea : public Sea {

	struct Ship {
		Ship() {}
		Ship(int positionTileX, int positionTileY, int sizeTileX, int sizeTileY, int seaPositionX, int seaPositionY, const sf::Texture& texture);
		void draw(sf::RenderWindow& window) { if (visible) window.draw(visual); }
		void setPosition(int tileX, int tileY);
		void rotate();
		void setMisplaced(bool a);
		bool getMisplaced() { return misplaced; }
		bool covers(int tileX, int tileY);
		int getSizeX() { return sizeTileX; }
		int getSizeY() { return sizeTileY; }
		int getPositionX() { return positionTileX; }
		int getPositionY() { return positionTileY; }
		bool visible{ true };
	private:
		int positionTileX;
		int positionTileY;
		int sizeTileX;
		int sizeTileY;
		int seaPositionX;
		int seaPositionY;
		bool misplaced{ false };
		sf::Sprite visual;
	};

	Ship fleet[SHIPS_COUNT];
	bool checkPlacement(int shipId);
public:
	AlliedSea(int positionX, int positionY);
	void draw(sf::RenderWindow& window);
	void setHit(int tileX, int tileY) { map[tileY][tileX].setStatus(Tile::hitAlly); }
	int getShipIdOnPosition(int tileX, int tileY);
	bool setShipsPosition(int shipId, int tileX, int tileY);
	bool rotateShip(int shipId);
};

#endif
