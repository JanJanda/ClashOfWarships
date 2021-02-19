#include "button.hpp"

Button::Button(int positionX, int positionY, const std::string& text) : positionX(positionX), positionY(positionY) {
	bcg.setPosition(positionX, positionY);
	txt.setFont(Resources::getStencil());
	txt.setString(text);
	txt.setCharacterSize(40);
	txt.setFillColor(sf::Color::White);
	centerText();
}

void Button::centerText() {
	float width = txt.getLocalBounds().width;
	float offset = (sizeX - width) / 2;
	txt.setPosition(positionX + offset - 3, positionY + 4);
}

bool Button::isClicked(const sf::Event& event) {
	return event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left &&
	event.mouseButton.x >= positionX && event.mouseButton.x < positionX + sizeX &&
	event.mouseButton.y >= positionY && event.mouseButton.y < positionY + sizeY;
}

void Button::setText(const std::string& text) {
	txt.setString(text);
	centerText();
}
