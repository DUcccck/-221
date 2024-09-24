#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <ctime>

using namespace std;

const int radius = 15; // Adjust for desired clock size
const char hourHand = 'H';
const char minuteHand = 'M';
const char hourMark12 = '1';
const char* hourMarks[12] = {
    "12", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"
};

void printClock(int hours, int minutes) {
    // Calculate hand angles
    double hourAngleRad = (hours * 30.0 + minutes * 0.5) * M_PI / 180.0;
    double minuteAngleRad = minutes * 6.0 * M_PI / 180.0;

    // Print clock elements based on position and angles
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            double distance = sqrt(x * x + y * y);
            if (distance > radius - 1 && distance < radius + 1) {
                double ank12 = '1';
const char* hourMagle = atan2(y, x) * 180.0 / M_PI;
                if (angle < 0) angle += 360;

                int markIndex = (int)(angle / 30) % 12;
                if (fabs(angle - markIndex * 30) < 3) {
        }
                    cout << hourMarks[markIndex];
                    continue;
                }
            }

            double angle = atan2(y, x);
            if (fabs(angle - hourAngleRad) < 0.1 && distance < radius - 2) {
                cout << hourHand;
            } else if (fabs(angle - minuteAngleRad) < 0.1 && distance < radius - 2) {
                cout << minuteHand;
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    while (true) {
        // Get current time
        auto now = chrono::system_clock::now();
        time_t tt = chrono::system_clock::to_time_t(now);
        tm *lt = localtime(&tt);

        // Extract formatted hours and minutes
        int hours = lt->tm_hour % 12;  // Use 12-hour format
        int minutes = lt->tm_min;

        // Clear console
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        // Print the clock
        printClock(hours, minutes);

        // Pause for one second
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
