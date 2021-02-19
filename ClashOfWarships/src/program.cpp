#include "program.hpp"

Program::Program(sf::RenderWindow& rw) : window(rw) {
	infoLine.setFont(Resources::getStencil());
	infoLine.setCharacterSize(40);
	infoLine.setFillColor(sf::Color::White);
	infoLine.setPosition(40, 490);

	for (int i = 0; i < helpLines; i++) {
		help[i].setFont(Resources::getStencil());
		help[i].setCharacterSize(40);
		help[i].setFillColor(sf::Color::White);
		help[i].setPosition(40, 40 + (60 * i));
	}
	help[0].setString("click on a ship to grab her");
	help[1].setString("then move your mouse to move the ship");
	help[2].setString("click again to release her if she is properly placed");
	help[3].setString("click right mouse button to rotate the held ship");
	help[4].setString("click READY button to wait for an opponent");
	help[5].setString("click JOIN button to connect to an opponent");

	helpClue.setFont(Resources::getStencil());
	helpClue.setCharacterSize(17);
	helpClue.setFillColor(sf::Color::White);
	helpClue.setString("Hold F1 for help");
	int posX = (windowWidth - helpClue.getLocalBounds().width) / 2;
	helpClue.setPosition(posX, windowHeight - 20);
}

bool Program::run() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			else acceptEvent(event);
		}
		newFrame();

		if (status == listening) {
			if (net.accept()) {
				setStatus(nothing);
				//hra
			}
		}
		if (status == join) {
			setStatus(nothing);
			if (net.join(enteredIP)) {
				//hra
			}
			else infoLine.setString("CONNECTION FAILED");
		}
	}
	return false;
}

void Program::acceptEvent(const sf::Event& event) {
	game.acceptEvent(event);
	if (readyButton.isClicked(event)) {
		if (status == listening) setStatus(nothing);
		else {
			setStatus(nothing);
			if (!game.setReady()) infoLine.setString("PLACE YOUR SHIPS PROPERLY");
			else if (!net.listen()) infoLine.setString("NETWORK FAILED");
			else setStatus(listening);
		}
	}
	if (joinButton.isClicked(event)) {
		if (status == catchIP) setStatus(nothing);
		else {
			setStatus(nothing);
			if (game.setReady()) setStatus(catchIP);
			else infoLine.setString("PLACE YOUR SHIPS PROPERLY");
		}
	}
	if (event.type == sf::Event::TextEntered) {
		if (status == catchIP) {
			sf::Uint32 c = event.text.unicode;
			if ((c >= 48 && c <= 57) || c == 46) enteredIP += c;
			infoLine.setString("IP ADDRESS: " + enteredIP);
		}
	}
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Enter) {
			if (status == catchIP) setStatus(join);
		}
		if (event.key.code == sf::Keyboard::F1)	showHelp = false;
	}
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::F1) showHelp = true;
	}
	if (event.type == sf::Event::LostFocus) {
		showHelp = false;
	}
}

void Program::setStatus(ProgramStatus newStatus) {
	if (newStatus == nothing) {
		game.setPreparation();
		infoLine.setString("");
		readyButton.setText("READY");
		joinButton.setText("JOIN");
	}
	else if (newStatus == listening) {
		game.setReady();
		infoLine.setString("WAITING FOR OPPONENT ON " + Network::getMyAddress());
		readyButton.setText("CANCEL");
		joinButton.setText("JOIN");
	}
	else if (newStatus == catchIP) {
		enteredIP = "";
		game.setReady();
		infoLine.setString("ENTER IP ADDRESS AND PRESS ENTER");
		readyButton.setText("READY");
		joinButton.setText("CANCEL");
	}
	else if (newStatus == join) {
		game.setReady();
		infoLine.setString("CONNECTING TO " + enteredIP);
		readyButton.setText("READY");
		joinButton.setText("WAIT");
	}
	status = newStatus;
}

void Program::newFrame() {
	window.clear();
	if (showHelp) for (int i = 0; i < helpLines; i++) window.draw(help[i]);
	else {
		window.draw(background);
		game.draw(window);
		readyButton.draw(window);
		joinButton.draw(window);
		window.draw(infoLine);
		window.draw(helpClue);
	}
	window.display();
}
