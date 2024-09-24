/*#include<iostream>
#include<boost/asio.hpp>
int main ()
{
    boost::asio::io_context io;
    boost::asio::steady_timer t(io,boost::asio::chrono::seconds(5));
    t.wait();
    std::cout<<"hellow word"<<std::endl;
    return 0;
} синхроне використання таймера */
/*
#include<iostream>
#include<boost/asio.hpp>

void print (const boost::system::error_code )
{
    std:: cout<<"Hellow WOrd"<<std::endl;
}
int main ()
{
    boost::asio::io_context io;
    boost::asio::steady_timer t (io,boost::asio::chrono::seconds(5));
    t.async_wait(&print);
    io.run();
    return 0;
}асинхроний таймер

#include <functional>
#include <iostream>
#include <boost/asio.hpp>

void print(const boost::system::error_code& ,
           boost::asio::steady_timer* t, int* count) {
    if (*count < 5) {
        std::cout << *count << std::endl;
        ++(*count);
        t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
        t->async_wait(std::bind(print, std::placeholders::_1, t, count));
    }
}

int main() {
    boost::asio::io_context io;
    int count = 0;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
    t.async_wait(std::bind(print, std::placeholders::_1, &t, &count));
    io.run();
    std::cout << "Останній підрахунок: " << count << std::endl;
    return 0;
}Timer.3 – прив’язка аргументів до обробника завершення


#include<functional>
#include<iostream>
#include<boost/asio.hpp>
class printer
{
    public:
    printer(boost::asio::io_context&io):
    timer_(io,boost::asio::chrono::seconds(1)),count_(0)
    {
        timer_.async_wait(std::bind(&printer::print,this));
    }
    ~printer()
    {
        std::cout<<"ostanim pidrahunmom ye "<< count_<<std::endl;
    }
    void print()
    {
        if(count_<5)
        {
            std::cout<<count_ <<std::endl;
            ++ count_;
            timer_.expires_at(timer_.expiry()+boost::asio::chrono::seconds(1));
            timer_.async_wait (std::bind(&printer::print,this));


        }
    }
    private:
    boost::asio::steady_timer timer_;
    int count_;
};
int main ()
{
    boost::asio::io_context io ;
    printer p (io);
    io.run();
    return 0;
}Timer.4 – використання функції-члена як обробника завершення


#include <functional>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>

class printer {
public:
    printer(boost::asio::io_context& io)
        : strand_(boost::asio::make_strand(io)),
          timer1_(io, boost::asio::chrono::seconds(1)),
          timer2_(io, boost::asio::chrono::seconds(1)),
          count_(0) {
        timer1_.async_wait(boost::asio::bind_executor(strand_,
            std::bind(&printer::print1, this)));
        timer2_.async_wait(boost::asio::bind_executor(strand_,
            std::bind(&printer::print2, this)));
    }

    ~printer() {
        std::cout << "Останній підрахунок: " << count_ << std::endl;
    }

    void print1() {
        if (count_ < 10) {
            std::cout << "Таймер 1: " << count_ << std::endl;
            ++count_;
            timer1_.expires_at(timer1_.expiry() + boost::asio::chrono::seconds(1));
            timer1_.async_wait(boost::asio::bind_executor(strand_,
                std::bind(&printer::print1, this)));
        }
    }

    void print2() {
        if (count_ < 10) {
            std::cout << "Таймер 2: " << count_ << std::endl;
            ++count_;
            timer2_.expires_at(timer2_.expiry() + boost::asio::chrono::seconds(1));
            timer2_.async_wait(boost::asio::bind_executor(strand_,
                std::bind(&printer::print2, this)));
        }
    }

private:
    boost::asio::strand<boost::asio::io_context::executor_type> strand_;
    boost::asio::steady_timer timer1_;
    boost::asio::steady_timer timer2_;
    int count_;
};

int main() {
    boost::asio::io_context io;
    printer p(io);
    std::thread t([&] { io.run(); });
    t.join();
    return 0;
}Timer.5 - Синхронізація обробників завершення в багатопоточних програмах
*/
#include <array> // Включаємо бібліотеку array для використання std::array
#include <iostream> // Включаємо бібліотеку iostream для використання std::cout і std::cerr
#include <boost/asio.hpp> // Включаємо бібліотеку Boost.Asio для роботи з асинхронним вводом/виводом

using boost::asio::ip::tcp; // Використовуємо простір імен boost::asio::ip::tcp для спрощення синтаксису

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) { // Перевіряємо, чи передано правильну кількість аргументів
            std::cerr << "Використання: клієнт <host>" << std::endl; // Виводимо повідомлення про неправильне використання
            return 0; // Завершуємо програму з кодом 0
        }

        boost::asio::io_context io; // Створюємо об'єкт io_context для керування асинхронними операціями
        tcp::resolver resolver(io); // Створюємо об'єкт resolver для вирішення адреси хоста
        tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "daytime"); // Виконуємо вирішення адреси хоста з використанням порту "daytime"
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

    return 0; // Завершуємо програму з кодом 0
}
