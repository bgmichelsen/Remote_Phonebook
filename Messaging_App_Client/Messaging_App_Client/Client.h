// This file contains the class definition for a chat client. The class will have functions to connect to a server, read
// from a server, write to a server, and disconnect from a server.
//
// Author: Brandon Michelsen

#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

class ChatClient {
public:
	// Constructor and deconstructor
	ChatClient(char* ipAddress);
	~ChatClient();

	// Connect and disconnect from server
	void connectToServer();
	void disconnectFromServer();

	// Write to and read from server
	void writeToServer(std::string message);
	void readFromServer();
private:
	const char* CHAT_PORT = "50013";

	boost::asio::io_service ioservice;

	boost::asio::ip::tcp::resolver resolver{ ioservice };
	boost::asio::ip::tcp::resolver::query query;
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator;
	boost::asio::ip::tcp::resolver::iterator end;

	boost::asio::ip::tcp::socket socket{ ioservice };
	boost::system::error_code error;
};
#endif
