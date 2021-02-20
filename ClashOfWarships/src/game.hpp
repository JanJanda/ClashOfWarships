#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "sea.hpp"

class Game {
	enum GameStatus { preparation, ready, myTurn, hisTurn };
	GameStatus status{ preparation };
	AlliedSea alsea{ 40, 80 };
	EnemySea ensea{ 520, 80 };
	int heldShip{ -1 };
	bool shipWellPlaced{ true };
	bool fired{ false };
	int firedX;
	int firedY;
	void processEventInPrep(const sf::Event& event);
	void processMyTurn(const sf::Event& event);
public:
	void draw(sf::RenderWindow& window) { ensea.draw(window); alsea.draw(window); }
	void acceptEvent(const sf::Event& event);
	bool setReady();
	void setPreparation() { status = preparation; }
	void start(bool myTurn);
	int getFiredX() { return firedX; }
	int getFiredY() { return firedY; }
	bool getFired() { return fired; }
	void reportImpact(bool hit);
	bool acceptImpact(int x, int y);
};

#endif
