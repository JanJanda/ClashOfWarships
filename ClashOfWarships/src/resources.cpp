#include "resources.hpp"
#include <fstream>

Resources::Resources() {
	message = "";
	if (!background.loadFromFile("background.png")) message += "background.png not found\n";
	if (!tile.loadFromFile("tile.png")) message += "tile.png not found\n";
	if (!carrier.loadFromFile("carrier.png")) message += "carrier.png not found\n";
	if (!battleship.loadFromFile("battleship.png")) message += "battleship.png not found\n";
	if (!cruiser.loadFromFile("cruiser.png")) message += "cruiser.png not found\n";
	if (!destroyer.loadFromFile("destroyer.png")) message += "destroyer.png not found\n";
	if (!submarine.loadFromFile("submarine.png")) message += "submarine.png not found\n";
	if (!rust.loadFromFile("rust.png")) message += "rust.png not found\n";
	if (!stencil.loadFromFile("stencil.ttf")) message += "stencil.ttf not found\n";

	if (message != "") report(message);
}

void Resources::report(const std::string& txt) {
	std::ofstream str("ERROR_MESSAGE.txt");
	str << "CLASH OF WARSHIPS\n";
	str << txt;
	str.close();
}
