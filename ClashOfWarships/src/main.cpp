#include <SFML/Graphics.hpp>
#include "resources.hpp"
#include "network.hpp"
#include "button.hpp"
#include "game.hpp"

int main()
{
	// TODO: error window a napoveda
	sf::Sprite background(Resources::getBackground()); // TODO: change color for efects
	sf::RenderWindow window(sf::VideoMode(960, 640), "Clash of Warships", sf::Style::Titlebar | sf::Style::Close);
	Game* game = new Game;

	sf::Text infoLine;
	infoLine.setFont(Resources::getStencil());
	infoLine.setCharacterSize(40);
	infoLine.setFillColor(sf::Color::White);
	infoLine.setPosition(40, 490);
	
	Button readyButton(320, 560, "READY");
	Button joinButton(520, 560, "JOIN");

	Network net;

	enum ProgramStatus { nothing, listening, catchIP, join };
	ProgramStatus status = nothing;
	std::string enteredIP = "";

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			else {
				game->acceptEvent(event);
				if (readyButton.isClicked(event)) {
					if (status == listening) {
						status = nothing;
						infoLine.setString("");
						readyButton.setText("READY");
						joinButton.setText("JOIN");
						game->setPreparation();
					}
					else {
						status = nothing;
						readyButton.setText("READY");
						joinButton.setText("JOIN");
						if (!game->setReady()) infoLine.setString("PLACE YOUR SHIPS PROPERLY");
						else if (!net.listen()) infoLine.setString("NETWORK FAILED");
						else {
							infoLine.setString("WAITING FOR OPPONENT ON " + Network::getMyAddress());
							readyButton.setText("CANCEL");
							status = listening;
						}
					}
				}
				if (joinButton.isClicked(event)) {
					if (status == catchIP) {
						status = nothing;
						game->setPreparation();
						infoLine.setString("");
						joinButton.setText("JOIN");
					}
					else {
						if (game->setReady()) {
							infoLine.setString("ENTER IP ADDRESS AND PRESS ENTER");
							joinButton.setText("CANCEL");
							enteredIP = "";
							status = catchIP;
						}
						else infoLine.setString("PLACE YOUR SHIPS PROPERLY");
					}
				}
				if (status == catchIP) {
					if (event.type == sf::Event::TextEntered) {
						sf::Uint32 c = event.text.unicode;
						if ((c >= 48 && c <= 57) || c == 46) enteredIP += c;
						infoLine.setString("IP ADDRESS: " + enteredIP);
					}
					if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) {
						status = join;
						infoLine.setString("CONNECTING TO " + enteredIP);
					}
				}
			}
		}

		window.clear();
		window.draw(background);
		game->draw(window);
		readyButton.draw(window);
		joinButton.draw(window);
		window.draw(infoLine);
		window.display();

		if (status == listening) {
			if (net.accept()) {
				status = nothing;
				infoLine.setString("ok lol");
				//hra
			}
		}
		if (status == join) {
			status = nothing;
			if (net.join(enteredIP)) {				
				infoLine.setString("ok test");
				//hra
			}
			else {
				infoLine.setString("CONNECTION FAILED");
				game->setPreparation();
			}
		}
	}
	delete game;
}
