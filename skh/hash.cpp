#include <iostream>
#include <string>
#include <openssl/sha.h> // Include OpenSSL header for SHA-256

using namespace std;

class Register {
public:
    string name;
    string password_create;

    void reg() {
        cout << "Enter username: ";
        getline(cin, name);

        if (name.empty()) {
            cout << "Invalid username. Please try again." << endl;
            reg();
            return;
        }

        cout << "Enter password (at least 8 characters): ";
        getline(cin, password_create);

        if (password_create.length() < 8) {
            cout << "Password should be at least 8 characters long. Please try again." << endl;
            reg();
            return;
        }

        cout << "Registration complete." << endl;
    }
};

class Hash : public Register {
public:
    string hash_pas;

    void hs() {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, password_create.c_str(), password_create.size());
        SHA256_Final(hash, &sha256);

        // Convert the hash to a hex string
        stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << hex << setw(2) << setfill('0') << (int)hash[i];
        }
        hash_pas = ss.str();

        cout << "Hashed password: " << hash_pas << endl;
    }
};

int main() {
    Hash a;

    a.reg();
    a.hs();

    return 0;
}
