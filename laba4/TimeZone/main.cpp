#include "timezone.h"
#include <iostream>

int main() {
    try {
        // Создаем объекты часовых поясов
        TimeZone defaultTz; // Использует Europe/Moscow по умолчанию
        TimeZone nyTz("America/New_York");

        // Получаем текущее время в разных часовых поясах
        auto moscowTime = defaultTz.getCurrentTime();
        auto nyTime = nyTz.getCurrentTime();

        std::cout << "Current time in Moscow: " << moscowTime << "\n";
        std::cout << "Current time in New York: " << nyTime << "\n";

        // Преобразуем системное время в локальное
        auto now = std::chrono::system_clock::now();
        auto moscowLocal = defaultTz.fromSystemTime(now);
        std::cout << "System time in Moscow: " << moscowLocal << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
