#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <boost/asio.hpp>
#include "contacts.h"
#include "directory.h"



int main() {
	std::cout << "testing program" << std::endl;
	Directory access;
	access.add_contact();
	system("pause");

	// test search for personal contact
	std::cout << "please in search " << std::endl;
	std::string usrInput;
	std::cin.ignore();
	std::getline(std::cin, usrInput); // ask for input
	Personal* Pcontact = access.search_for_personal_contact(usrInput);
	if (Pcontact == nullptr)
		std::cout << "\nContact not found\n";
	else 
		Pcontact->print_contact_info();

	// test search for business contact
	std::cout << "please in search " << std::endl;
	std::getline(std::cin, usrInput); // ask for input
	Business* Bcontact = access.search_for_business_contact(usrInput);
	if (Bcontact == nullptr)
		std::cout << "\nContact not found\n";
	else
		Bcontact->print_contact_info();

	system("pause");
	return 0;
}


/*
using boost::asio::ip::tcp;

// function that creates a tring to be sent back to the client
std::string make_daytime_string()
{
	using namespace std; // for time_t, time and ctime
	time_t now = time(0); // store system time value 0
	return ctime(&now);
}
int main()
{
	try
	{
		boost::asio::io_service io_service;
		// this object is created to listen for new connections
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));

		for (;;)
		{
			// this socket represents the connection to the client
			tcp::socket socket(io_service);
			// wait for connection
			acceptor.accept(socket);

			// client connects to our service. determine current time 
			// and tranfer info to client 
			std::string message = make_daytime_string();

			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}*/