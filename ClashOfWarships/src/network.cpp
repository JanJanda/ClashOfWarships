#include "network.hpp"

Network::Network() {
	listener.setBlocking(false);
}

bool Network::listen() {
	return listener.listen(port) == sf::Socket::Done;
}

bool Network::accept() {
	return listener.accept(sock) == sf::Socket::Done;
}

bool Network::join(const std::string& address) {
	return sock.connect(address, port, sf::seconds(5)) == sf::Socket::Done;
}
