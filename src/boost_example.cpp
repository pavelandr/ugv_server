#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;

#include <iostream>

int main() {
    try {
        io_context io;

        // Create an endpoint for the server to listen on port 8080
        tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 8080));

        std::cout << "Server is running. Waiting for connections..." << std::endl;

        // Start accepting connections
        tcp::socket socket(io);
        acceptor.accept(socket);

        std::string message = "Hello, World!\n";

        // Send the message
        boost::system::error_code ignored_error;
        boost::asio::write(socket, buffer(message), ignored_error);

        std::cout << "Message sent to client!" << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
