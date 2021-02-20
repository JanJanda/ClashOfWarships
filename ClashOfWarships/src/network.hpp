#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <SFML/Network.hpp>

class Network {
	static const int port = 52218;
	sf::TcpListener listener;
	sf::TcpSocket sock;
public:
	Network();
	bool listen();
	bool accept();
	bool join(const std::string& address);
	void sendFire(sf::Uint8 tileX, sf::Uint8 tileY);
	sf::Socket::Status receiveFire(sf::Uint8& tileX, sf::Uint8& tileY);
	void sendImpact(bool hit);
	sf::Socket::Status receiveImpact(bool& hit);
	static std::string getMyAddress() { return sf::IpAddress::getLocalAddress().toString(); }
	void setBlocking(bool b) { sock.setBlocking(b); }
};

#endif
