#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <thread>
#include <memory>
#include <list>

using boost::asio::ip::tcp;

int main(void) {
	boost::asio::io_service io_service;
	std::list<std::unique_ptr<tcp::socket>> sockets;

	const unsigned short port = 12345;

	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));
	auto listen = [&]() {
		std::cout << "Waiting connection." << std::endl;

		std::unique_ptr<tcp::socket> socket(new tcp::socket(io_service));
		acceptor.accept(*socket);
		sockets.push_back(std::move(socket));

		std::cout << sockets.size() << " clients connected." << std::endl;
	};
	listen();
	std::thread([&]() {
			while(true) listen();
			}).detach();

	while (true) {
		std::cout << "Type a server message: ";
		std::string message;
		std::getline(std::cin, message);
		const std::string delimiter = "\n";
		message.append(delimiter);

		for(auto s = sockets.begin(); s != sockets.end(); ++s) {
			boost::system::error_code error_code;
			boost::asio::write(**s, boost::asio::buffer(message), error_code);
			if (error_code == boost::asio::error::broken_pipe) {
				std::cout << "A client disconect." << std::endl;
				s = sockets.erase(s);
				--s;
			}
		}
	}

	return 0;
}
