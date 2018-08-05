// This is the main file for the client-side of our chat application. It has the functionality to send
// commands to the server asking to add a contact to the phonebook or to receive information about a 
// particular contact.
// 
// Authors: Brandon Michelsen & William Bryant

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

int main() {
	const char* CHAT_PORT = "50013";
	std::string inputIP;

	try {
		std::cout << "Please enter a Server Address: ";
		std::getline(std::cin, inputIP);

		boost::asio::io_service ioservice;
		boost::asio::ip::tcp::resolver resolver(ioservice);
		boost::asio::ip::tcp::resolver::query query(inputIP, CHAT_PORT);
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		boost::asio::ip::tcp::resolver::iterator end;

		boost::asio::ip::tcp::socket socket(ioservice);
		boost::system::error_code error = boost::asio::error::host_not_found;

		while (error && (endpoint_iterator != end)) {
			socket.close();
			socket.connect(*endpoint_iterator++, error);
		}

		if (error)
			throw boost::system::system_error(error);

		std::cout << "\nConnection to server successful...\n";

		for (;;) {
			boost::array<char, 40> buf;
			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				break;
			else if (error)
				throw boost::system::system_error(error);

			std::cout.write(buf.data(), len);
			std::cout << "\nDone\n";

			std::string message;
			std::getline(std::cin, message);
			boost::asio::write(socket, boost::asio::buffer(message));
		}
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::cout << "\nClosing the connection...\n";
	system("pause");
	return 0;
}