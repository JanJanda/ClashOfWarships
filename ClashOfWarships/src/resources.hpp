#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <SFML/Graphics.hpp>

class Resources {
	Resources();
	static const Resources& get() { static Resources instance; return instance; }
	void report(const std::string& txt);
	std::string message;
	sf::Texture background;
	sf::Texture tile;
	sf::Texture carrier;
	sf::Texture battleship;
	sf::Texture cruiser;
	sf::Texture destroyer;
	sf::Texture submarine;
	sf::Texture rust;
	sf::Font stencil;
public:
	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;
	static const std::string& getMessage() { return get().message; }
	static const sf::Texture& getBackground() { return get().background; }
	static const sf::Texture& getTile() { return get().tile; }
	static const sf::Texture& getCarrier() { return get().carrier; }
	static const sf::Texture& getBattleship() { return get().battleship; }
	static const sf::Texture& getCruiser() { return get().cruiser; }
	static const sf::Texture& getDestroyer() { return get().destroyer; }
	static const sf::Texture& getSubmarine() { return get().submarine; }
	static const sf::Texture& getRust() { return get().rust; }
	static const sf::Font& getStencil() { return get().stencil; }
};

#endif
