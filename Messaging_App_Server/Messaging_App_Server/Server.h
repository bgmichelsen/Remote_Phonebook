// This file has the definition for a chat server. It has functions for receiving a client connection, closing
// a client connection, reading a client message, and writing a message to the client.
//
// Author: Brandon Michelsen

#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

class ChatServer {
public:
	// Constructor and deconstructor
	ChatServer();
	~ChatServer();

	// Connect and disconnect from client
	void connectToClient();
	void disconnectFromClient();

	// Write to and read from client
	void writeToClient(std::string message);
	void readFromClient();
private:
	boost::asio::io_service ioservice;

	boost::asio::ip::tcp::endpoint endpoint;
	boost::asio::ip::tcp::acceptor acceptor;
	boost::asio::ip::tcp::socket socket;
	boost::system::error_code error;

	const char* CHAT_PORT = "50013";
};
#endif