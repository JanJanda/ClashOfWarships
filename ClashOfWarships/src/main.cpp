#include <SFML/Graphics.hpp>

int main()
{
	sf::Texture bcgTexture;
	if (!bcgTexture.loadFromFile("background.jpg")) return 0; // TODO: error window
	sf::Sprite background(bcgTexture); // TODO: change color for efects
	sf::RenderWindow window(sf::VideoMode(960, 640), "Clash of Warships", sf::Style::Titlebar | sf::Style::Close);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}
		window.clear(sf::Color::Black);
		window.draw(background);

		window.display();
	}
}
