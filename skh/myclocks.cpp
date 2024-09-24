#include <iostream>
#include <chrono>
#include <iomanip> // Для setw та setfill
#include <thread> // Для sleep_for

using namespace std;
using namespace std::chrono;

void perevorm(int& minutes, int& hours, int& sek) {
    if (sek == 59&&minutes==59) {    
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        char per[4] = {'/', '-', '\\', '|'};
        int sminutes = minutes * 10;
        int shours=hours%10;
        for (int i = 0; i < 4; ++i) {
            cout << shours<<per[i] << ":"
                  << per[i]<<per[i] << endl;
            this_thread::sleep_for(milliseconds(400)); // Затримка 400 мс
           
        }}
     else if (sek == 59&&minutes%10==9) {    
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        char per[4] = {'/', '-', '\\', '|'};
        int sminutes = minutes * 10;
        for (int i = 0; i < 4; ++i) {
            cout << hours << ":"
                  << per[i]<<per[i] << endl;
            this_thread::sleep_for(milliseconds(400)); // Затримка 400 мс
           
        }
    }
    else if (sek == 59) {    
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        char per[4] = {'/', '-', '\\', '|'};
        int sminutes = minutes % 10;
        for (int i = 0; i < 4; ++i) {
            cout << hours << ":"
                 << sminutes  << per[i] << endl;
            this_thread::sleep_for(milliseconds(400)); // Затримка 400 мс
           
        }
    }
}

void perevorh(int& hours, int& minutes, int& sek) {
    // Заглушка для функції
}

int main() {
    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        // Отримати поточний час
        auto now = system_clock::now();

        // Конвертувати у часову точку (time_point)
        time_t tt = system_clock::to_time_t(now);
        tm local_tm = *localtime(&tt);

        // Отримати години та хвилини
        int hours = local_tm.tm_hour;  // Години (24-годинний формат)
        int minutes = local_tm.tm_min; // Хвилини
        int sek = local_tm.tm_sec;     // Секунди

        // Вивести години та хвилини у форматі HH:MM
        cout << setw(2) << setfill('0') << hours << ":"
             << setw(2) << setfill('0') << minutes << endl;

        // Перевірка часу для оновлення
        if (sek == 59) {
            perevorm(minutes, hours, sek);
            if (minutes == 59) {
                perevorh(hours, minutes, sek);
            }
        }

        // Затримка на 1 секунду
        this_thread::sleep_for(seconds(1));
    }

    return 0;
}
