#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

const int max_length = 1024;

void client(boost::asio::io_context& io_context, const std::string& host, unsigned short port) {
    try {
        tcp::socket socket(io_context);
        tcp::resolver resolver(io_context);
        boost::asio::connect(socket, resolver.resolve(host, std::to_string(port)));

        for (;;) {
            std::cout << "Enter message: ";
            char request[max_length];
            std::cin.getline(request, max_length);
            size_t request_length = strlen(request);

            boost::asio::write(socket, boost::asio::buffer(request, request_length));

            char reply[max_length];
            size_t reply_length = boost::asio::read(socket, boost::asio::buffer(reply, request_length));

            std::cout << "Received: ";
            std::cout.write(reply, reply_length);
            std::cout << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in client: " << e.what() << std::endl;
    }
}

int main() {
    try {
        boost::asio::io_context io_context;
        client(io_context, "127.0.0.1", 8888);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
