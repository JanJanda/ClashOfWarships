#include "program.hpp"

int main(int argc, char** args)
{
	int port = 52218;
	if (argc >= 2) {
		try {
			port = std::stoi(*(args + 1));
		}
		catch (...) {}
	}

	sf::RenderWindow window(sf::VideoMode(Program::windowWidth, Program::windowHeight), "Clash of Warships", sf::Style::Titlebar | sf::Style::Close);
	bool again = true;
	while (again) {
		Program* prog = new Program(window, port);
		again = prog->run();
		delete prog;
	}
}
