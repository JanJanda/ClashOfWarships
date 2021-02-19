#include "program.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(Program::windowWidth, Program::windowHeight), "Clash of Warships", sf::Style::Titlebar | sf::Style::Close);
	Program* p = new Program(window);
	while (p->run()) {
		delete p;
		p = new Program(window);
	}
}
