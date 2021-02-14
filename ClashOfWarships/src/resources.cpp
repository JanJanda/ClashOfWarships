#include "resources.hpp"

Resources::Resources() {
	message = "";
	if (!background.loadFromFile("background.png")) message = "background.png not found";
	if (!tile.loadFromFile("tile.png")) message = "tile.png not found";
	if (!carrier.loadFromFile("carrier.png")) message = "carrier.png not found";
	if (!battleship.loadFromFile("battleship.png")) message = "battleship.png not found";
	if (!cruiser.loadFromFile("cruiser.png")) message = "cruiser.png not found";
	if (!destroyer.loadFromFile("destroyer.png")) message = "destroyer.png not found";
	if (!submarine.loadFromFile("submarine.png")) message = "submarine.png not found";
}
