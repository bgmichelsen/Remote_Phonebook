// This is the main file for the client-side of our chat application. It has the functionality to send
// commands to the server asking to add a contact to the phonebook or to receive information about a 
// particular contact.
// 
// Authors: Brandon Michelsen & William Bryant

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using namespace boost::system;
using namespace boost::asio;
using namespace boost::asio::ip;

int main() {
	// Local variables
	const char* CHAT_PORT = "50013"; // Port for app communication
	std::string input_IP; // Input for the server's IP address

						  // Opening screen
	std::cout << "\t\tAirwave Phonebook: The remote phonebook\n";
	std::cout << "\nWelcome to the Airwave Phonebook, your digital remote phone directory. This application ";
	std::cout << "allows you to remotely store and manage your contacts, whether they are business or personal.\n";
	std::cout << "To use this application, you first need to connect to an external server running the directory ";
	std::cout << "management application. After establishing a connection, you can then use the app to add contacts, ";
	std::cout << "search for information about a particular contact, or even sort the phone directory.\n";
	std::cout << "The phonebook includes several aspects of a contact. For a personal contact, it stores the ";
	std::cout << "name of the contact, the phonenumber of the contact, and a nickname for the contact. ";
	std::cout << "For a business contact, it stores the contact\'s name, number, and the business they work at.\n\n";

	system("pause");
	system("cls");

	// Try/catch for catching network errors
	try {
		// Get the server's IP address of hostname from the user
		std::cout << "Please enter a Server Address: ";
		std::getline(std::cin, input_IP);

		// Setup a network connection to the server
		io_service ioservice;
		tcp::resolver resolver(ioservice);
		tcp::resolver::query query(input_IP, CHAT_PORT);
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::resolver::iterator end;

		tcp::socket socket(ioservice);
		error_code error = error::host_not_found;

		// Look for the host connection
		while (error && (endpoint_iterator != end)) {
			socket.close();
			socket.connect(*endpoint_iterator++, error);
		}

		if (error)
			throw boost::system::system_error(error);

		std::cout << "\nConnection to server successful...\n\n";
		system("pause");
		system("cls");

		// While loop for connection to the server
		for (;;) {
			// Read in data from the server
			boost::array<char, 4096> buf;
			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == error::eof)
				break;
			else if (error)
				throw system_error(error);

			std::cout.write(buf.data(), len);

			// Send data to the server
			std::string message;
			std::getline(std::cin, message);

			message = "$" + message; // Added an extra $ because sending an empty string to the server broke the program

			write(socket, buffer(message));
			system("pause");
			system("cls");
		}
	}
	catch (std::exception& e) {
		// Catch errors
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\nClosing the connection...\n";
	system("pause");
	return 0;
}