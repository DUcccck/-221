#include<iostream>
#include<boost/asio.hpp>
using namespace std;
using boost::asio::ip::tcp;
class searsh{
    public:
    void sea (){
       
    }
    protected:
    void delet(){

    }
}
class send : public search{
    protected:
    void handle_client(tcp::socket& socket) {
    try {
        std::array<char, 128> buf;
        boost::system::error_code error;

        while (true) {
            size_t len = socket.read_some(boost::asio::buffer(buf), error);

            if (error == boost::asio::error::eof) {
                break; // Connection closed cleanly by peer.
            } else if (error) {
                throw boost::system::system_error(error); // Some other error.
            }

            std::cout.write(buf.data(), len);
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in handle_client: " << e.what() << "\n";
    }
    }
    void tel(){
         try {
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));

        std::cout << "Server is running..." << std::endl;

        for (;;) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::cout << "Client connected!" << std::endl;
            handle_client(socket);
        }
        } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        }}


int main( ){
    
}