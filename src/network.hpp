#include <SFML/network.hpp>
using namespace std;

sf::TcpSockket socket;
sf::Socket::Status status = socket.connect("19.2.168.1.1", 12345);  //CAN CHANGE NOT SURE
if (status != sf::Socket:Done)
{
    // error...
}
sf::TcpListener listener;

// listener is set to this port
if (listener.listen(12345) != sf::Socket::Done)
{
	// error
}
sf::TcpSocket client;
if (listener.accept(client) != sf::Socket::Done)
{
    // error...
}
 //usees client to com with the connectied client \\ and continue to accept more connections with listener
sf::UdpSocket socket;
//socket -> port
if (socket.bind(12345) != sf::Socket::Done);																				//can change all chars to any data types
{
	//error
}
char data[100] = ...;
//TCP
if (socket.send(data, 100) != sf::Socket::Done)
{
	// error...
}
//UPD
sf::IpAddress recipient = "192.168.1.1";								//IP TO CONNECT TO
unsigned short port = 12345;
if (socket.send(data, 100, recipient, port) != sf::Socket::Done)
{
	//error
}
char data[100];
std::size_t received;
//TCP socket
if (socket.receive(data, 100, recieved) != sf::Socket::Done)
{
	error
}
std::cout << "Received " << received << " bytes" << std::endl;

//UDP Socket
sf:IpAddress: sender;
unsigned short port;
if (socket.receive(data, 100, received,sender, port) != sf::Socket::Done)
{
	//error...
}
std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;
sf::TcpSocket socket;
sf::SocketSelector selector;
selector.add(socket);
if (selector.wait(sf::seconds(10)))
{
	//received stuffy stuffy
}
else
{
	//timeout reached, nothing was recieved
}
if (selector.wait(sf::seconds(10)))
{
	// sockets
{
	if (selector.isReady(socket))
	{
		 // this socket is ready, you can receive (or accept if it's a listener)
		socket.recieve(...);
		}
	}
}
sf::Socket::status receiveWithTimeout(sf::TcpSocket& socket, sf::Packet& packet, sf::Time timeout)
{
sf::SocketSelector selector;
selector.add(socket);
if (selector.wait(timeout))
	return socket.receive(packet);
else
	return sf::Socket::NotReady
}
sf::TcpSocket tcpSocket;
tcpSocket.setBlocking(false);

sf:TcpListener listenerSocket;
listenerSocket.setBlocking(false);

sf::UdpSocket;
udpSocket updSocket.setBlocking(false);