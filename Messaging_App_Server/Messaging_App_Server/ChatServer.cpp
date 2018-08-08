// This is the main file for the client-side of our chat application. It has the functionality to receive 
// commands from the client application to add contacts to a directory or display contact information. 
//
// Authors: Brandon Michelsen & William Bryant

#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "directory.h"
#include "contacts.h"

namespace {
	// Create a variable for the main menu of the program
	const std::string MENU = "\t\tSERVER MESSAGE\n\nThe following is the menu for the Airwave Phonebook application. Enter these values to perform the associated actions:\n\t1) Enter a new contact\n\t2) Search for a particular contact\n\t3) Sort the contact list\n\t4) View the phonebook\n\t5) Close the connection\n\n";
}

// Function prototypes
std::string readRemoteInput(boost::asio::ip::tcp::socket& connection, boost::system::error_code& error); // Function for reading user input from a remote computer
void viewPhoneBook(boost::asio::ip::tcp::socket& connection, boost::system::error_code& error, Directory* list); // Function to view the phonebook

int main() {
	// Local variables
	const int CHAT_PORT = 50013; // Port for app communication
	std::string clientMsg; // Variable for storing messages from the client
	Directory phonebook; // Phonebook for storing contact information

	try {
		// Setup a connection to a client
		boost::asio::io_service ioservice;
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), CHAT_PORT);
		boost::asio::ip::tcp::acceptor acceptor(ioservice, endpoint);
		boost::asio::ip::tcp::socket socket(ioservice);

		std::cout << "\nServer is ready...\n";

		boost::system::error_code error = boost::asio::error::host_not_found;

		acceptor.accept(socket);

		for (;;) {
			// Print out the menu and the user to enter something
			boost::asio::write(socket, boost::asio::buffer("\n"));
			boost::asio::write(socket, boost::asio::buffer(MENU));
			boost::asio::write(socket, boost::asio::buffer("Please enter a value from the menu:\n"));

			// Read the user's input
			clientMsg = readRemoteInput(socket, error);

			// Check what the user had inputted
			if (clientMsg == "1") {
				std::string contactType;
				std::string contactName;
				std::string contactNumber;
				std::string contactInfo;

				boost::asio::write(socket, boost::asio::buffer("\nPlease enter what type of contact you would like to add (business/personal):\n"));
				contactType = readRemoteInput(socket, error);

				boost::asio::write(socket, boost::asio::buffer("\nPlease enter the name of the contact:\n"));
				contactName = readRemoteInput(socket, error);

				boost::asio::write(socket, boost::asio::buffer("\nPlease enter the contact\'s number:\n"));
				contactNumber = readRemoteInput(socket, error);

				boost::asio::write(socket, boost::asio::buffer("\nPlease enter additional information (nickname for personal contact, company name for business):\n"));
				contactInfo = readRemoteInput(socket, error);

				if ((contactType == "business" || contactType == "Business") || (contactType == "personal" || contactType == "Personal"))
					phonebook.add_contact(contactType, contactName, contactNumber, contactInfo);
				else
					boost::asio::write(socket, boost::asio::buffer("\nThat is not a correct contact type.\n"));
			}
			else if (clientMsg == "2") {
				std::string contactType;
				std::string searchTerm;

				boost::asio::write(socket, boost::asio::buffer("\nPlease enter what type of contact you would like to search for (business/personal):\n"));
				contactType = readRemoteInput(socket, error);

				boost::asio::write(socket, boost::asio::buffer("\nPlease enter a search term (e.g. name, phone number, or nickname/company):\n"));
				searchTerm = readRemoteInput(socket, error);

				if (contactType == "business" || contactType == "Business") {
					Business* foundContact;

					foundContact = phonebook.search_for_business_contact(searchTerm);

					if (foundContact == nullptr) {
						boost::asio::write(socket, boost::asio::buffer("\nContact not found.\n"));
					}
					else {
						boost::asio::write(socket, boost::asio::buffer("\nContact Name:\n"));
						boost::asio::write(socket, boost::asio::buffer(foundContact->get_name()));
						boost::asio::write(socket, boost::asio::buffer("\nContact number:\n"));
						boost::asio::write(socket, boost::asio::buffer(foundContact->get_phone()));
						boost::asio::write(socket, boost::asio::buffer("\nContact company:\n"));
						boost::asio::write(socket, boost::asio::buffer(foundContact->get_company()));
					}
				}
				else if (contactType == "personal" || contactType == "Personal") {
					Personal* foundContact;

					foundContact = phonebook.search_for_personal_contact(searchTerm);

					if (foundContact == nullptr) {
						boost::asio::write(socket, boost::asio::buffer("\nContact not found.\n"));
					}
					else {
						boost::asio::write(socket, boost::asio::buffer("\nContact Name:\n"));
						boost::asio::write(socket, boost::asio::buffer(foundContact->get_name()));
						boost::asio::write(socket, boost::asio::buffer("\nContact number:\n"));
						boost::asio::write(socket, boost::asio::buffer(foundContact->get_phone()));
						boost::asio::write(socket, boost::asio::buffer("\nContact company:\n"));
						boost::asio::write(socket, boost::asio::buffer(foundContact->get_nickname()));
					}
				}
				else {
					boost::asio::write(socket, boost::asio::buffer("\nThat is not the correct type of contact.\n"));
				}
			}
			else if (clientMsg == "3") {
				if (phonebook.is_empty()) {
					boost::asio::write(socket, boost::asio::buffer("\nCannot sort phonebook. Phonebook is empty.\n"));
				}
				else {
					boost::asio::write(socket, boost::asio::buffer("\nSorting contacts...\n"));
					phonebook.sort_phonebook_by_name();
					boost::asio::write(socket, boost::asio::buffer("\nDone...\n"));
				}
			}
			else if (clientMsg == "4") {
				if (phonebook.is_empty())
					boost::asio::write(socket, boost::asio::buffer("\nThe phonebook is empty.\n"));
				else
					viewPhoneBook(socket, error, &phonebook);
			}
			else if (clientMsg == "5") {
				socket.close();
				break;
			}
			else {
				boost::asio::write(socket, boost::asio::buffer("\nThat is not a valid command\n"));
			}
		}
	}
	catch (std::exception& e) {
		std::cerr << "\nException: " << e.what() << std::endl;
	}

	std::cout << "\nServer closing\n";
	system("pause");
	return 0;
}

std::string readRemoteInput(boost::asio::ip::tcp::socket& connection, boost::system::error_code& error) {
	boost::array<char, 40> message;
	std::string returnMsg;
	size_t length;

	for (;;) {
		length = connection.read_some(boost::asio::buffer(message), error);

		if (error == boost::asio::error::eof)
			break;
		else if (error)
			throw boost::system::system_error(error);

		std::cout << "\nMessage from client: ";
		std::cout.write(message.data(), length);
		break;
	}

	for (unsigned int i = 0; i < length; i++)
		returnMsg += message[i];

	return returnMsg;
}

void viewPhoneBook(boost::asio::ip::tcp::socket& connection, boost::system::error_code& error, Directory* list) {
	std::string userChoice;
	boost::asio::write(connection, boost::asio::buffer("What type of contact list would you like to view (business/personal): "));
	userChoice = readRemoteInput(connection, error);

	if (userChoice == "business" || userChoice == "Business") {
		std::vector<Business*>* displayList = list->return_business_contact_book();

		for (unsigned int i = 0; i < displayList->size(); i++) {
			Business* contactElement = displayList->at(i);
			boost::asio::write(connection, boost::asio::buffer("\nContact Name:\n"));
			boost::asio::write(connection, boost::asio::buffer(contactElement->get_name()));
			boost::asio::write(connection, boost::asio::buffer("\nContact Number:\n"));
			boost::asio::write(connection, boost::asio::buffer(contactElement->get_phone()));
			boost::asio::write(connection, boost::asio::buffer("\nContact Workplace:\n"));
			boost::asio::write(connection, boost::asio::buffer(contactElement->get_company()));
			boost::asio::write(connection, boost::asio::buffer("\n"));
		}
	}
	else if (userChoice == "personal" || userChoice == "Personal") {
		std::vector<Personal*>* displayList = list->return_personal_contact_book();

		for (unsigned int i = 0; i < displayList->size(); i++) {
			Personal* contactElement = displayList->at(i);
			boost::asio::write(connection, boost::asio::buffer("\nContact Name:\n"));
			boost::asio::write(connection, boost::asio::buffer(contactElement->get_name()));
			boost::asio::write(connection, boost::asio::buffer("\nContact Number:\n"));
			boost::asio::write(connection, boost::asio::buffer(contactElement->get_phone()));
			boost::asio::write(connection, boost::asio::buffer("\nContact Workplace:\n"));
			boost::asio::write(connection, boost::asio::buffer(contactElement->get_nickname()));
			boost::asio::write(connection, boost::asio::buffer("\n"));
		}
	}
	else {
		boost::asio::write(connection, boost::asio::buffer("\nThat is not a valid option.\n"));
	}
}