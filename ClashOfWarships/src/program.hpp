#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <SFML/Graphics.hpp>
#include "resources.hpp"
#include "network.hpp"
#include "button.hpp"
#include "game.hpp"

class Program {
	enum ProgramStatus { nothing, listening, catchIP, join, sendFire, receiveFire, receiveImpact, victory, defeat };
	ProgramStatus status{ nothing };
	sf::Sprite background{ Resources::getBackground() };
	sf::RenderWindow& window;
	Game game;
	sf::Text infoLine;
	Button readyButton{ 320, 560, "READY" };
	Button joinButton{ 520, 560, "JOIN" };
	Network net;
	std::string enteredIP{ "" };
	sf::Text help;
	bool showHelp{ false };
	sf::Text helpClue;

	void acceptEvent(const sf::Event& event);
	void setStatus(ProgramStatus newStatus);
	void newFrame();
public:
	static const int windowWidth = 960;
	static const int windowHeight = 640;
	Program(sf::RenderWindow& rw);
	bool run();
};

#endif
