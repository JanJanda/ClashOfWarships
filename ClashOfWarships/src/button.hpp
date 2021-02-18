#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "resources.hpp"

class Button {
	const int sizeX = 120;
	const int sizeY = 60;
	sf::Sprite bcg{ sf::Sprite(Resources::getRust()) };
	sf::Text txt;
	int positionX;
	int positionY;
	void centerText();
public:
	Button(int positionX, int positionY, const std::string& text);
	void draw(sf::RenderWindow& window) { window.draw(bcg); window.draw(txt); }
	bool isClicked(const sf::Event& event);
};

#endif
