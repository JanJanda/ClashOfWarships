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
	int allyHealth;
	int enemyHealth;
	void processEventInPrep(const sf::Event& event);
	void processMyTurn(const sf::Event& event);
public:
	Game();
	void draw(sf::RenderWindow& window) { ensea.draw(window); alsea.draw(window); }
	void acceptEvent(const sf::Event& event);
	bool setReady();
	void setPreparation() { status = preparation; }
	void gaming(bool myTurn);
	int getFiredX() { fired = false; return firedX; }
	int getFiredY() { fired = false; return firedY; }
	bool getFired() { return fired; }
	int getAllyHealth() { return allyHealth; }
	int getEnemyHealth() { return enemyHealth; }
	void acceptImpact(bool hit);
	bool reportImpact(int x, int y);
};

#endif
