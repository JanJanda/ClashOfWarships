#include "program.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(960, 640), "Clash of Warships", sf::Style::Titlebar | sf::Style::Close);
	Program* p = new Program(window);
	while (p->run()) {
		delete p;
		p = new Program(window);
	}
}
