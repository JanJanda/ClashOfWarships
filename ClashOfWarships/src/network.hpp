#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <SFML/Network.hpp>

class Network {
	int port;
	sf::TcpListener listener;
	sf::TcpSocket sock;
public:
	Network(int port);
	bool listen();
	void stopListening() { listener.close(); }
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
