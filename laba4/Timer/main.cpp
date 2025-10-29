#include <iostream>
#include "timer.h"

int main() {
    Timer timer;

    // 1. Запуск таймера
    timer.StartTimer();
    std::cout << "Таймер запущен\n";

    // 2. Измерение времени выполнения блока кода
    std::cout << "Выполняем вычисления...\n";
    for (int i = 0; i < 100000000; i++) {
        // Имитация работы
    }

    std::cout << "Прошло времени: " << timer.GetSeconds() << " сек\n";

    // 3. Использование WaitTimer
    std::cout << "Ждем 2 секунды...\n";
    timer.WaitTimer(5);
    std::cout << "Прошло времени: " << timer.GetSeconds() << " сек\n";

    // 4. Остановка таймера
    timer.EndTimer();
    std::cout << "Таймер остановлен. Итоговое время: "
              << timer.GetSeconds() << " сек\n";

    // 5. Сброс
    timer.ResetTimer();
    std::cout << "Таймер сброшен. Состояние: "
              << (timer.RunningTimer() ? "запущен" : "остановлен") << "\n";

    return 0;
}
