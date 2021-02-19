#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "sea.hpp"

class Game {
	enum GameStatus { preparation, ready };
	GameStatus status{ preparation };
	AlliedSea alsea{ AlliedSea(40, 80) };
	EnemySea ensea{ EnemySea(520, 80) };
	int heldShip{ -1 };
	bool shipWellPlaced{ true };
	void processEventInPrep(const sf::Event& event);
public:
	void draw(sf::RenderWindow& window) { ensea.draw(window); alsea.draw(window); }
	void acceptEvent(const sf::Event& event);
	bool setReady();
	void setPreparation() { status = preparation; }
};

#endif
