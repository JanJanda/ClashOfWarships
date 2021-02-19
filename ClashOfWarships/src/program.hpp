#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <SFML/Graphics.hpp>
#include "resources.hpp"
#include "network.hpp"
#include "button.hpp"
#include "game.hpp"

class Program {
	enum ProgramStatus { nothing, listening, catchIP, join };
	ProgramStatus status{ nothing };
	sf::Sprite background{ Resources::getBackground() };
	sf::RenderWindow& window;
	Game game;
	sf::Text infoLine;
	Button readyButton{ 320, 560, "READY" };
	Button joinButton{ 520, 560, "JOIN" };
	Network net;
	std::string enteredIP{ "" };

	void acceptEvent(const sf::Event& event);
	void setStatus(ProgramStatus newStatus);
	void newFrame();
public:
	Program(sf::RenderWindow& rw);
	bool run();
};

#endif
