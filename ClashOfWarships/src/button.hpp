#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "resources.hpp"

class Button {
	static const int sizeX = 120;
	static const int sizeY = 60;
	sf::Sprite bcg{ Resources::getRust() };
	sf::Text txt;
	int positionX;
	int positionY;
	void centerText();
public:
	bool visible{ true };
	Button(int positionX, int positionY, const std::string& text);
	void draw(sf::RenderWindow& window) { if (visible) { window.draw(bcg); window.draw(txt); } }
	bool isClicked(const sf::Event& event);
	void setText(const std::string& text);
};

#endif
