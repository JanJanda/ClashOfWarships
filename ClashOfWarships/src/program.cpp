#include "program.hpp"

Program::Program(sf::RenderWindow& rw, int netPort) : window(rw), net(netPort) {
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
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (status == victory || status == defeat || status == disconnected) {
				if (readyButton.isClicked(event)) return true;
				if (joinButton.isClicked(event)) window.close();
			}
			if (event.type == sf::Event::Closed) window.close();
			else acceptEvent(event);
		}
		newFrame();

		if (status != victory && status != defeat && status != disconnected) {
			if (game.getAllyHealth() <= 0) setStatus(defeat);
			if (game.getEnemyHealth() <= 0) setStatus(victory);
		}

		if (status == receiveFire) {
			sf::Uint8 x, y;
			sf::Socket::Status st = net.receiveFire(x, y);
			if (st == sf::Socket::Done) {
				bool aux = game.reportImpact(x, y);
				if (!aux) setStatus(sendFire);
				net.sendImpact(aux);
			}
			else if (st == sf::Socket::Disconnected || st == sf::Socket::Error) setStatus(disconnected);
		}
		if (status == sendFire) {
			if (game.getFired()) {
				setStatus(receiveImpact);
				net.sendFire(game.getFiredX(), game.getFiredY());
			}
		}
		if (status == receiveImpact) {
			bool hit;
			sf::Socket::Status st = net.receiveImpact(hit);
			if (st == sf::Socket::Done) {
				game.acceptImpact(hit);
				if (hit) setStatus(sendFire);
				else setStatus(receiveFire);
			}
			else if (st == sf::Socket::Disconnected || st == sf::Socket::Error) setStatus(disconnected);
		}

		if (status == listening) {
			if (net.accept()) setStatus(sendFire);
		}
		if (status == join) {
			if (net.join(enteredIP)) setStatus(receiveFire);
			else {
				setStatus(nothing);
				infoLine.setString("CONNECTION FAILED");
			}
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
		net.stopListening();
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
		net.stopListening();
		game.setReady();
		infoLine.setString("ENTER IP ADDRESS AND PRESS ENTER");
		readyButton.setText("READY");
		joinButton.setText("CANCEL");
	}
	else if (newStatus == join) {
		net.stopListening();
		game.setReady();
		infoLine.setString("CONNECTING TO " + enteredIP);
		readyButton.setText("READY");
		joinButton.setText("WAIT");
	}
	else if (newStatus == sendFire) {
		net.stopListening();
		net.setBlocking(false);
		game.gaming(true);
		infoLine.setString("FIRE!!!");
		readyButton.visible = false;
		joinButton.visible = false;
	}
	else if (newStatus == receiveFire) {
		net.stopListening();
		net.setBlocking(false);
		game.gaming(false);
		infoLine.setString("WAIT");
		readyButton.visible = false;
		joinButton.visible = false;
	}
	else if (newStatus == receiveImpact) {
		net.stopListening();
		net.setBlocking(false);
		game.gaming(false);
		infoLine.setString("WAIT");
		readyButton.visible = false;
		joinButton.visible = false;
	}
	else if (newStatus == victory) {
		net.stopListening();
		game.setReady();
		background.setColor(sf::Color::Blue);
		infoLine.setString("VICTORY");
		readyButton.setText("RESET");
		readyButton.visible = true;
		joinButton.setText("CLOSE");
		joinButton.visible = true;
	}
	else if (newStatus == defeat) {
		net.stopListening();
		game.setReady();
		background.setColor(sf::Color::Red);
		infoLine.setString("DEFEAT");
		readyButton.setText("RESET");
		readyButton.visible = true;
		joinButton.setText("CLOSE");
		joinButton.visible = true;
	}
	else if (newStatus == disconnected) {
		net.stopListening();
		game.setReady();
		background.setColor(sf::Color(0x7f7f7fff));
		infoLine.setString("CONNECTION LOST");
		readyButton.setText("RESET");
		readyButton.visible = true;
		joinButton.setText("CLOSE");
		joinButton.visible = true;
	}
	status = newStatus;
	newFrame();
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
