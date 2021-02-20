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
	sf::Socket::Status st = sf::Socket::Partial;
	while (st == sf::Socket::Partial) st = sock.send(pack);
}

sf::Socket::Status Network::receiveFire(sf::Uint8& tileX, sf::Uint8& tileY) {
	sf::Packet pack;
	sf::Socket::Status st = sock.receive(pack);
	if (st == sf::Socket::Done) pack >> tileX >> tileY;
	return st;
}

void Network::sendImpact(bool hit) {
	sf::Packet pack;
	pack << hit;
	sf::Socket::Status st = sf::Socket::Partial;
	while (st == sf::Socket::Partial) st = sock.send(pack);
}

sf::Socket::Status Network::receiveImpact(bool& hit) {
	sf::Packet pack;
	sf::Socket::Status st = sock.receive(pack);
	if (st == sf::Socket::Done) pack >> hit;
	return st;
}
