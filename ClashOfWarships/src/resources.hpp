#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <SFML/Graphics.hpp>

class Resources {
	std::string message;
	sf::Texture background;
	sf::Texture tile;
	sf::Texture carrier;
	sf::Texture battleship;
	sf::Texture cruiser;
	sf::Texture destroyer;
	sf::Texture submarine;
public:
	Resources();
	const std::string& getMessage() const { return message; }
	const sf::Texture& getBackground() const { return background; }
	const sf::Texture& getTile() const { return tile; }
	const sf::Texture& getCarrier() const { return carrier; }
	const sf::Texture& getBattleship() const { return battleship; }
	const sf::Texture& getCruiser() const { return cruiser; }
	const sf::Texture& getDestroyer() const { return destroyer; }
	const sf::Texture& getSubmarine() const { return submarine; }
};

#endif
