
#include <array> // Включаємо бібліотеку array для використання std::array
#include <iostream> // Включаємо бібліотеку iostream для використання std::cout і std::cerr
#include <boost/asio.hpp> // Включаємо бібліотеку Boost.Asio для роботи з асинхронним вводом/виводом

using boost::asio::ip::tcp; // Використовуємо простір імен boost::asio::ip::tcp для спрощення синтаксису

int main(int argc, char* argv[]) {
    try {
        /*if (argc != 2) { // Перевіряємо, чи передано правильну кількість аргументів
            std::cerr << "Використання: клієнт <host>" << std::endl; // Виводимо повідомлення про неправильне використання
            return 0;
        }*/ 

        boost::asio::io_context io; // Створюємо об'єкт io_context для керування асинхронними операціями
        std::string ip_adress="217.196.161.218";
        tcp::resolver resolver(io); // Створюємо об'єкт resolver для вирішення адреси хоста
        tcp::resolver::results_type endpoints = resolver.resolve(ip_adress, "1234"); // Виконуємо вирішення адреси хоста з використанням порту "daytime"
        tcp::socket socket(io); // Створюємо об'єкт socket для підключення до сервера
        boost::asio::connect(socket, endpoints); // Підключаємо сокет до одного з endpoint

        for (;;) { // Запускаємо безкінечний цикл для читання даних з сервера
            std::array<char, 128> buf; // Створюємо буфер для зберігання отриманих даних
            boost::system::error_code error; // Створюємо об'єкт для зберігання коду помилки
            size_t len = socket.read_some(boost::asio::buffer(buf), error); // Читаємо дані з сокета

            if (error == boost::asio::error::eof) { // Перевіряємо, чи було з'єднання закрито коректно
                break; // Виходимо з циклу, якщо з'єднання закрите
            } else if (error) { // Перевіряємо наявність інших помилок
                throw boost::system::system_error(error); // Кидаємо виняток у випадку іншої помилки
            }

            std::cout.write(buf.data(), len); // Виводимо отримані дані на екран
        }
    } catch (std::exception& e) { // Ловимо всі винятки типу std::exception
        std::cerr << e.what() << std::endl; // Виводимо повідомлення про помилку
    }

    return 0; 
}
