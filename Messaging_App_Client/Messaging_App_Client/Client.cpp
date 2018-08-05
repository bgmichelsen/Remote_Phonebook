// This file contains the function definitions for the ChatClient class
//
// Author: Brandon Michelsen

#include "Client.h"

// Constructor
ChatClient::ChatClient(char* ipAddress) 
	: query(ipAddress, CHAT_PORT) {};

// Deconstructor
ChatClient::~ChatClient() {
	socket.close();
}

// Connect to server
void ChatClient::connectToServer() {

}