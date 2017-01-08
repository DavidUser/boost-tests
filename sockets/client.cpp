#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>

int main() {
	boost::asio::io_service io_service;

	using boost::asio::ip::tcp;

	tcp::resolver resolver(io_service);
	const unsigned short port = 12345;
	tcp::resolver::query query("localhost", std::to_string(port));
	tcp::resolver::iterator endpoint = resolver.resolve(query);

	tcp::socket socket(io_service);
	boost::asio::connect(socket, endpoint);
	
	boost::system::error_code error;
	do {
		boost::array<char, 3> buffer;
		std::size_t bytesReaded = socket.read_some(boost::asio::buffer(buffer), error);
		std::cout.write(buffer.data(), bytesReaded);
		if (error) std::cerr << "An error occur: " << error.message() << std::endl;
	} while (error != boost::asio::error::eof);

	return 0;
}
