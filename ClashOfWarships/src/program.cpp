#include "program.hpp"

Program::Program(sf::RenderWindow& rw) : window(rw) {
	infoLine.setFont(Resources::getStencil());
	infoLine.setCharacterSize(40);
	infoLine.setFillColor(sf::Color::White);
	infoLine.setPosition(40, 490);

	help.setFont(Resources::getStencil());
	help.setCharacterSize(40);
	help.setFillColor(sf::Color::White);
	help.setPosition(40, 40);
	help.setString("click on a ship to grab her\nthen move your mouse to move the ship\nclick again to release her if she is properly placed\nclick right mouse button to rotate the held ship\nclick READY button to wait for an opponent\nclick JOIN button to connect to an opponent");

	helpClue.setFont(Resources::getStencil());
	helpClue.setCharacterSize(17);
	helpClue.setFillColor(sf::Color::White);
	helpClue.setString("Hold F1 for help");
	int posX = (windowWidth - helpClue.getLocalBounds().width) / 2;
	helpClue.setPosition(posX, windowHeight - 20);
}

bool Program::run() {
	bool receiveFire = false;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			else acceptEvent(event);
		}
		newFrame();

		if (receiveFire) {
			receiveFire = false;
			sf::Uint8 x, y;
			net.receiveFire(x, y);
			net.sendImpact(game.acceptImpact(x, y));
		}
		if (status == listening) {
			if (net.accept()) {
				setStatus(gameOn);
				game.start(true);
			}
		}
		if (status == join) {
			setStatus(nothing);
			if (net.join(enteredIP)) {
				setStatus(gameOn);
				game.start(false);
				receiveFire = true;
			}
			else infoLine.setString("CONNECTION FAILED");
		}
		if (game.getFired()) {
			net.sendFire(game.getFiredX(), game.getFiredY());
			game.reportImpact(net.receiveImpact());
			receiveFire = true;
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
	else if (newStatus == gameOn) {
		infoLine.setString("");
		readyButton.visible = false;
		joinButton.visible = false;
	}
	status = newStatus;
}

void Program::newFrame() {
	window.clear(sf::Color(0x444454ff));
	if (showHelp) window.draw(help);
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
