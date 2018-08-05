// This is the main file for the client-side of our chat application. It has the functionality to receive 
// commands from the client application to add contacts to a directory or display contact information. 
//
// Authors: Brandon Michelsen & William Bryant

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

int main() {
	const int CHAT_PORT = 50013;
	
	try {
		boost::asio::io_service ioservice;
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), CHAT_PORT);
		boost::asio::ip::tcp::acceptor acceptor(ioservice, endpoint);
		boost::asio::ip::tcp::socket socket(ioservice);

		std::cout << "\nServer is ready...\n";

		boost::system::error_code error = boost::asio::error::host_not_found;

		acceptor.accept(socket);

		for (;;) {
			std::string message("\nGeneral Kenobi!\n");
			boost::asio::write(socket, boost::asio::buffer(message));
			for (;;) {
				boost::array<char, 40> buf;
				size_t length = socket.read_some(boost::asio::buffer(buf), error);

				if (error == boost::asio::error::eof)
					break;
				else if (error)
					throw boost::system::system_error(error);

				std::cout << "\nMessage from client: ";
				std::cout.write(buf.data(), length);
				break;
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