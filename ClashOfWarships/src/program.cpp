#include "program.hpp"

Program::Program(sf::RenderWindow& rw) : window(rw) {
	infoLine.setFont(Resources::getStencil());
	infoLine.setCharacterSize(40);
	infoLine.setFillColor(sf::Color::White);
	infoLine.setPosition(40, 490);
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
	if (status == catchIP) {
		if (event.type == sf::Event::TextEntered) {
			sf::Uint32 c = event.text.unicode;
			if ((c >= 48 && c <= 57) || c == 46) enteredIP += c;
			infoLine.setString("IP ADDRESS: " + enteredIP);
		}
		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) setStatus(join);
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
	window.draw(background);
	game.draw(window);
	readyButton.draw(window);
	joinButton.draw(window);
	window.draw(infoLine);
	window.display();
}
