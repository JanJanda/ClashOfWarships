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

void Network::sendFire(sf::Uint8 tileX, sf::Uint8 tileY) {
	sf::Packet pack;
	pack << tileX << tileY;
	sock.send(pack);
}

void Network::receiveFire(sf::Uint8& tileX, sf::Uint8& tileY) {
	sf::Packet pack;
	sock.receive(pack);
	pack >> tileX >> tileY;
}

void Network::sendImpact(bool hit) {
	sf::Packet pack;
	pack << hit;
	sock.send(pack);
}

bool Network::receiveImpact() {
	sf::Packet pack;
	sock.receive(pack);
	bool ret;
	pack >> ret;
	return ret;
}
