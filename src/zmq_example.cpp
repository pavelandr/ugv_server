#include <zmq.hpp>
#include <iostream>
#include <string>

int main() {
    // Prepare the ZeroMQ context and REP socket
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::rep);
    
    // Bind the socket to a TCP port
    socket.bind("tcp://*:5555");
    
    std::cout << "Server is running. Waiting for connections..." << std::endl;
    
    while (true) {
        zmq::message_t request;

        // Wait for the next request from the client
        socket.recv(request, zmq::recv_flags::none);
        std::string received_message(static_cast<char*>(request.data()), request.size());
        
        std::cout << "Received: " << received_message << std::endl;

        // Create the reply message
        std::string reply_message = "Hello, Client!";
        zmq::message_t reply(reply_message.size());
        memcpy(reply.data(), reply_message.c_str(), reply_message.size());

        // Send the reply to the client
        socket.send(reply, zmq::send_flags::none);
    }

    return 0;
}
