// This is the main file for the client-side of our chat application. It has the functionality to receive 
// commands from the client application to add contacts to a directory or display contact information. 
//
// Authors: Brandon Michelsen & William Bryant

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "directory.h"
#include "contacts.h"

using namespace boost::system;
using namespace boost::asio;
using namespace boost::asio::ip;

// Function prototypes
std::string read_remote_input(tcp::socket& connection, error_code& error); // Function for reading user input from a remote computer
void view_phone_book(tcp::socket& connection, error_code& error, Directory* list); // Function to view the phonebook
bool is_phone_number(std::string number); // Function to check the validity of an entered phone number

int main() {
	// Local variables
	const int CHAT_PORT = 50013; // Port for app communication
	int client_message; // Variable for storing messages from the client
	Directory phonebook; // Phonebook for storing contact information

	// Enum for checking menu values
	enum MENU { 
		NEW_CONTACT, 
		SEARCH_CONTACTS,
		SORT_CONTACTS,
		VIEW_CONTACTS,
		CLOSE_CONNECTION
	};

	// Try-catch for networking aspects of the code
	try {
		// Setup a connection to a client
		io_service ioservice;
		tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), CHAT_PORT);
		tcp::acceptor acceptor(ioservice, endpoint);
		tcp::socket socket(ioservice);

		std::cout << "\nServer is ready...\n";

		error_code error = boost::asio::error::host_not_found;

		acceptor.accept(socket);

		// While loop for sending and receiving data from the client
		for (;;) {
			// Print out the menu and the user to enter something
			write(socket, buffer("\n"));
			write(socket, buffer("\t\tSERVER MESSAGE\n"));
			write(socket, buffer("\nThe following is the menu for the Airwave Phonebook application. "));
			write(socket, buffer("Enter these values to perform the associated actions:\n"));
			write(socket, buffer("\t1) Enter a new contact\n"));
			write(socket, buffer("\t2) Search for a particular contact\n"));
			write(socket, buffer("\t3) Sort the contact list\n"));
			write(socket, buffer("\t4) View the phonebook\n"));
			write(socket, buffer("\t5) Close the connection\n"));

			write(socket, buffer("\nPlease enter a value from the menu:\n"));

			// Read the user's input (subtract 1 to fit in with the MENU enumerator
			client_message = stoi(read_remote_input(socket, error)) - 1;

			// Check what the user had inputted
			switch (client_message) {
				// Create a new contact
			case MENU::NEW_CONTACT: 
			{
				// Local data
				std::string contact_type;
				std::string contact_name;
				std::string contact_number;
				std::string contact_info;

				write(socket, buffer("\nPlease enter what type of contact you would like to add (business/personal):\n"));
				contact_type = read_remote_input(socket, error);

				// Add the new contact if the contact type is business or personal
				if (contact_type == "BUSINESS" || contact_type == "PERSONAL") {
					write(socket, buffer("\nPlease enter the name of the contact:\n"));
					contact_name = read_remote_input(socket, error);

					write(socket, buffer("\nPlease enter the contact\'s number:\n"));
					contact_number = read_remote_input(socket, error);

					// Make sure the user enters the phone number in a valid format
					while (!is_phone_number(contact_number)) {
						write(socket, buffer("\nThat is not a valid phone number.\n"));
						write(socket, buffer("\nPlease enter the contact\'s number:\n"));
						contact_number = read_remote_input(socket, error);
					}

					write(socket, buffer("\nPlease enter additional information (nickname for personal contact, company name for business):\n"));
					contact_info = read_remote_input(socket, error);

					phonebook.add_contact(contact_type, contact_name, contact_number, contact_info);
				}
				else
					write(socket, buffer("\nThat is not a valid contact type.\n"));
				break;
			}
				// Search for a particular contact
			case MENU::SEARCH_CONTACTS:
			{
				// Local variables
				std::string contact_type;
				std::string search_term;
				Contact* found_contact = nullptr;

				write(socket, buffer("\nPlease enter what type of contact you would like to search for (business/personal):\n"));
				contact_type = read_remote_input(socket, error);

				// Only search for data if the contact type is business or personal
				if (contact_type == "BUSINESS" || contact_type == "PERSONAL") {
					write(socket, buffer("\nPlease enter a search term (e.g. name, phone number, or nickname/company):\n"));
					search_term = read_remote_input(socket, error);

					// Get the pointer to the particular contact
					found_contact = phonebook.search_for_business_contact(search_term);

					if (found_contact == nullptr) {
						// If pointer is null, contact is not found
						write(socket, buffer("\nContact not found.\n"));
					}
					else {
						// Otherwise, print out the data
						write(socket, buffer("\nContact Name:\n"));
						write(socket, buffer(found_contact->get_name()));
						write(socket, buffer("\nContact number:\n"));
						write(socket, buffer(found_contact->get_phone()));
						write(socket, buffer("\nContact company:\n"));
						if (contact_type == "BUSINESS")
							// If the contact type is business, print the company
							write(socket, buffer(((Business*)found_contact)->get_company()));
						else if (contact_type == "PERSONAL")
							// If the contact type is personal, print the nickname
							write(socket, buffer(((Personal*)found_contact)->get_nickname()));
					}
				}
				break;
			}
				// Sort contacts
 			case MENU::SORT_CONTACTS:
			{
				if (phonebook.is_empty())
					// If the phone book is empty, cannot sort
					write(socket, buffer("\nCannot sort phonebook. Phonebook is empty.\n"));
				else {
					// Otherwise, sort the phone book
					write(socket, buffer("\nSorting contacts...\n"));
					phonebook.sort_phonebook_by_name();
					write(socket, buffer("\nDone...\n"));
				}
				break;
			}
				// View contacts
			case MENU::VIEW_CONTACTS:
			{
				if (phonebook.is_empty())
					// If the phone book is empty, cannot view phone book
					write(socket, buffer("\nThe phonebook is empty.\n"));
				else
					// Otherwise, view the phone book
					view_phone_book(socket, error, &phonebook);
				break;
			}
				// Close the connection
			case MENU::CLOSE_CONNECTION:
			{
				socket.close();
				break;
			}
			default:
			{
				// Default is that the entered data is incorrect
				write(socket, buffer("\nThat is not a valid command\n"));
				break;
			}
			} // switch (clientMsg)
			// Continue the program (for display formatting)
			write(socket, buffer("\nPress any key to continue..."));
			read_remote_input(socket, error);
		}
	}
	catch (std::exception& e) {
		// Catch all exceptions
		std::cerr << "\nException: " << e.what() << std::endl;
	}

	std::cout << "\nServer closing\n";
	system("pause");
	return 0;
}

// Function for reading in data from the client (accepts parameters for TCP/IP socket and an error code)
std::string read_remote_input(tcp::socket& connection, error_code& error) {
	// Local variables
	boost::array<char, 40> message; // Buffer for the message
	std::string return_message; // String message to return
	size_t length = connection.read_some(buffer(message), error); // Length of data received

	std::cout << "\nMessage from client: ";
	std::cout.write(message.data(), length);

	// Add the characters in the buffer to the string
	for (unsigned int i = 1; i < length; i++)
		return_message += message[i];

	// Capaitalize all characters in the string
	std::transform(return_message.begin(), return_message.end(), return_message.begin(), ::toupper);

	return return_message;
}

// Function for viewing the phone book (accepts parameters for TCP/IP socket, an error code, and a pointer to a	Directory object)
void view_phone_book(tcp::socket& connection, error_code& error, Directory* list) {
	// Local variables
	write(connection, buffer("What type of contact list would you like to view (business/personal): "));
	std::string user_choice = read_remote_input(connection, error); // Variable for the type of contact
	std::vector<Contact*>* display_list = nullptr; // Pointer to vector of Contact object pointers

	if (user_choice == "BUSINESS")
		// If user selects business, return a business Contact list
		display_list = (std::vector<Contact*>*)list->return_business_contact_book();
	else if (user_choice == "PERSONAL")
		// If user selects personal, return personal Contact list
		display_list = (std::vector<Contact*>*)list->return_personal_contact_book();

	// Display the data for the phone book
	for (unsigned int i = 0; i < display_list->size(); i++) {
		Contact* contact_element = display_list->at(i);
		write(connection, buffer("\nContact Name:\n"));
		write(connection, buffer(contact_element->get_name()));
		write(connection, buffer("\nContact Number:\n"));
		write(connection, buffer(contact_element->get_phone()));
		write(connection, buffer("\nContact Info:\n"));
		// Display contact-type depedentant information
		if (user_choice == "BUSINESS")
			write(connection, buffer(((Business*)contact_element)->get_company()));
		else if (user_choice == "PERSONAL")
			write(connection, buffer(((Personal*)contact_element)->get_nickname()));
		write(connection, buffer("\n"));
	}
}

// Function to check for a valid phone number
bool is_phone_number(std::string number) {
	std::regex phone("[[:digit:]]{3}-[[:digit:]]{3}-[[:digit:]]{4}");

	return (std::regex_match(number, phone));
}