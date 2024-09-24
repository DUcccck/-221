#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;
using namespace std;

int main() {
    try {
        io_service service;
        ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 2001);
        ip::tcp::socket sock(service);

        sock.connect(ep);
        cout << "Successfully connected to server!" << endl;
    }
    catch (boost::system::system_error &e) {
        cerr << "Error1 " << e.what() << endl;
    }

    return 0;
}  

