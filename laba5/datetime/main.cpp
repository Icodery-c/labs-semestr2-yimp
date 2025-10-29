#include "datetime.h"
#include <iostream>
#include <iomanip>
#include <clocale>
#include <chrono>
#include <limits>
#include <stdexcept>
#include <fstream>
#include <vector>

using namespace std;

// Функции для проверки валидности временных зон
bool isTimeZoneValid(const string& tz) {
    try {
        std::chrono::locate_zone(tz);
        return true;
    } catch (...) {
        return false;
    }
}

bool isValidUTCOffset(const string& tz) {
    if (tz.size() < 4 || tz.size() > 9) return false;
    if (tz.substr(0, 3) != "UTC") return false;

    if (tz[3] == '+' || tz[3] == '-') {
        size_t colon_pos = tz.find(':');
        if (colon_pos != string::npos) {
            if (tz.size() != 9) return false;
            string hours = tz.substr(4, 2);
            string minutes = tz.substr(7, 2);
            if (!isdigit(hours[0]) || !isdigit(hours[1]) || !isdigit(minutes[0]) || !isdigit(minutes[1]))
                return false;
            int h = stoi(hours);
            int m = stoi(minutes);
            return (h >= 0 && h <= 23 && m >= 0 && m <= 59);
        } else {
            string hour_part = tz.substr(4);
            if (hour_part.empty()) return false;
            for (char c : hour_part) if (!isdigit(c)) return false;
            int h = stoi(hour_part);
            return (h >= 0 && h <= 23);
        }
    }
    return false;
}

// Функции для ввода данных с проверками
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

Date inputDate() {
    int d, m, y;
    char sep1, sep2;
    while (true) {
        cout << "Введите дату в формате ДД.ММ.ГГГГ: ";
        if (!(cin >> d >> sep1 >> m >> sep2 >> y) || sep1 != '.' || sep2 != '.') {
            clearInputBuffer();
            cerr << "Ошибка формата! Используйте формат ДД.ММ.ГГГГ\n";
            continue;
        }
        try {
            return Date(d, m, y);
        } catch (const char* e) {
            cerr << "Ошибка: " << e << ". Попробуйте снова.\n";
            clearInputBuffer();
        }
    }
}

Time inputTime() {
    int h, min, s;
    char sep1, sep2;
    while (true) {
        cout << "Введите время в формате ЧЧ:ММ:СС: ";
        if (!(cin >> h >> sep1 >> min >> sep2 >> s) || sep1 != ':' || sep2 != ':') {
            clearInputBuffer();
            cerr << "Ошибка формата! Используйте формат ЧЧ:ММ:СС\n";
            continue;
        }
        try {
            return Time(h, min, s);
        } catch (const char* e) {
            cerr << "Ошибка: " << e << ". Попробуйте снова.\n";
            clearInputBuffer();
        }
    }
}

string inputTimeZone() {
    string tz;
    while (true) {
        cout << "Введите часовой пояс (например Europe/Moscow, UTC+3): ";
        cin >> tz;
        if (isTimeZoneValid(tz) || isValidUTCOffset(tz)) {
            return tz;
        }
        cerr << "Некорректный часовой пояс. Попробуйте снова.\n";
        clearInputBuffer();
    }
}

// Шаблонная функция для тестирования стека
template <typename T>
void testStack() {
    Stack<T> stack;
    int choice;

    while (true) {
        cout << "\n=== Тестирование стека ==="
             << "\nТекущий размер стека: " << stack.getSize()
             << "\n1. Добавить элемент (push)"
             << "\n2. Извлечь элемент (pop)"
             << "\n3. Вставить элемент по индексу"
             << "\n4. Удалить элемент по индексу"
             << "\n5. Найти элемент"
             << "\n6. Показать все элементы"
             << "\n7. Проверить пустоту стека"
             << "\n0. Вернуться"
             << "\nВыбор: ";

        if (!(cin >> choice)) {
            clearInputBuffer();
            cerr << "Ошибка ввода! Попробуйте снова.\n";
            continue;
        }

        try {
            switch (choice) {
                case 1: {
                    cout << "Введите данные для элемента:\n";
                    T* item = nullptr;

                    if constexpr (is_same_v<T, DateTime>) {
                        item = new T(inputDate(), inputTime());
                    }
                    else if constexpr (is_same_v<T, DateTimeWithTimeZone>) {
                        item = new T(inputDate(), inputTime(), inputTimeZone());
                    }
                    else if constexpr (is_same_v<T, Timer>) {
                        item = new T(inputDate(), inputTime(), false);
                    }

                    stack.push(item);
                    cout << "Элемент добавлен.\n";
                    break;
                }
                case 2: {
                    T* item = stack.pop();
                    if (item) {
                        cout << "Извлеченный элемент: " << *item << endl;
                        delete item;
                    } else {
                        cout << "Стек пуст.\n";
                    }
                    break;
                }
                case 3: {
                    int index;
                    cout << "Введите индекс для вставки: ";
                    if (!(cin >> index)) {
                        clearInputBuffer();
                        cerr << "Ошибка ввода индекса!\n";
                        break;
                    }

                    cout << "Введите данные для элемента:\n";
                    T* item = nullptr;

                    if constexpr (is_same_v<T, DateTime>) {
                        item = new T(inputDate(), inputTime());
                    }
                    else if constexpr (is_same_v<T, DateTimeWithTimeZone>) {
                        item = new T(inputDate(), inputTime(), inputTimeZone());
                    }
                    else if constexpr (is_same_v<T, Timer>) {
                        item = new T(inputDate(), inputTime(), false);
                    }

                    stack.insert(index, item);
                    cout << "Элемент вставлен.\n";
                    break;
                }
                case 4: {
                    int index;
                    cout << "Введите индекс для удаления: ";
                    if (!(cin >> index)) {
                        clearInputBuffer();
                        cerr << "Ошибка ввода индекса!\n";
                        break;
                    }
                    stack.removeAt(index);
                    cout << "Элемент удален.\n";
                    break;
                }
                case 5: {
                    cout << "Введите данные для поиска:\n";
                    T item = []() {
                        if constexpr (is_same_v<T, DateTime>) {
                            return T(inputDate(), inputTime());
                        }
                        else if constexpr (is_same_v<T, DateTimeWithTimeZone>) {
                            return T(inputDate(), inputTime(), inputTimeZone());
                        }
                        else if constexpr (is_same_v<T, Timer>) {
                            return T(inputDate(), inputTime(), false);
                        }
                    }();

                    int index = stack.find(item);
                    if (index != -1) {
                        cout << "Элемент найден на позиции: " << index << endl;
                    } else {
                        cout << "Элемент не найден.\n";
                    }
                    break;
                }
                case 6: {
                    cout << "Элементы стека:\n";
                    stack.display();
                    break;
                }
                case 7: {
                    cout << "Стек " << (stack.isEmpty() ? "пуст" : "не пуст") << endl;
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Неверный выбор!\n";
                    clearInputBuffer();
            }
        } catch (const char* e) {
            cerr << "Ошибка: " << e << endl;
            clearInputBuffer();
        } catch (const exception& e) {
            cerr << "Исключение: " << e.what() << endl;
            clearInputBuffer();
        }
    }
}

// Тестирование таймера
void testTimer() {
    cout << "\n=== Тестирование Таймера ===\n";
    Timer timer;
    int choice;

    while(true) {
        cout << "\n1. Запустить таймер\n"
             << "2. Остановить таймер\n"
             << "3. Сбросить таймер\n"
             << "4. Получить прошедшее время\n"
             << "5. Ожидание\n"
             << "0. Выход\n"
             << "Выбор: ";

        if (!(cin >> choice)) {
            clearInputBuffer();
            cerr << "Ошибка ввода! Попробуйте снова.\n";
            continue;
        }

        try {
            switch(choice) {
                case 1:
                    timer.StartTimer();
                    cout << "Таймер запущен в: " << timer << endl;
                    break;
                case 2:
                    timer.StopTimer();
                    cout << "Таймер остановлен в: " << timer << endl;
                    break;
                case 3:
                    timer.ResetTimer();
                    cout << "Таймер сброшен до: " << timer << endl;
                    break;
                case 4: {
                    int seconds = timer.GetSeconds();
                    int ms = timer.GetMilliseconds();
                    cout << "Прошло времени: " << seconds << " секунд (" << ms << " мс)\n";
                    cout << "Текущее время: " << timer << endl;
                    break;
                }
                case 5: {
                    int sec;
                    cout << "Введите секунды для ожидания: ";
                    if (!(cin >> sec)) {
                        clearInputBuffer();
                        cerr << "Ошибка ввода!\n";
                        break;
                    }
                    timer.WaitTimer(sec);
                    cout << "Ожидание " << sec << " секунд завершено\n";
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Неверный выбор!\n";
                    clearInputBuffer();
            }
        } catch(const char* e) {
            cerr << "Ошибка: " << e << endl;
            clearInputBuffer();
        } catch(const exception& e) {
            cerr << "Исключение: " << e.what() << endl;
            clearInputBuffer();
        }
    }
}

// Тестирование часовых поясов
void testTimeZone() {
    cout << "\n=== Тестирование Часовых поясов ===\n";
    DateTimeWithTimeZone dtz;
    string tz;
    int choice;

    while(true) {
        cout << "\nТекущий часовой пояс: " << dtz.getTimeZone() << endl;
        cout << "1. Установить часовой пояс\n"
             << "2. Показать текущее время\n"
             << "0. Выход\n"
             << "Выбор: ";

        if (!(cin >> choice)) {
            clearInputBuffer();
            cerr << "Ошибка ввода! Попробуйте снова.\n";
            continue;
        }

        try {
            switch(choice) {
                case 1: {
                    bool valid = false;
                    while (!valid) {
                        cout << "Введите часовой пояс (например Europe/Moscow, UTC+3): ";
                        cin >> tz;
                        if (isTimeZoneValid(tz) || isValidUTCOffset(tz)) {
                            dtz.setTimeZone(tz);
                            cout << "Часовой пояс установлен на: " << dtz.getTimeZone() << endl;
                            valid = true;
                        } else {
                            cout << "Некорректный часовой пояс. Попробуйте снова.\n";
                            clearInputBuffer();
                        }
                    }
                    break;
                }
                case 2: {
                    auto zt = dtz.getCurrentTime();
                    auto now = std::chrono::system_clock::now();
                    auto local_time = std::chrono::current_zone()->to_local(now);
                    cout << "Время в выбранном поясе: " << std::format("{:%d.%m.%Y %H:%M:%S}", zt.get_local_time()) << endl;
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Неверный выбор!\n";
                    clearInputBuffer();
            }
        } catch(const char* e) {
            cerr << "Ошибка: " << e << endl;
            clearInputBuffer();
        } catch(const exception& e) {
            cerr << "Исключение: " << e.what() << endl;
            clearInputBuffer();
        }
    }
}

// Главное меню
int main() {
    setlocale(LC_ALL, "Russian");
    int choice;

    while(true) {
        cout << "\n=== Главное меню ==="
             << "\n1. Тестирование стека DateTime"
             << "\n2. Тестирование стека DateTimeWithTimeZone"
             << "\n3. Тестирование стека Timer"
             << "\n4. Тестирование таймера"
             << "\n5. Тестирование часовых поясов"
             << "\n0. Выход"
             << "\nВыбор: ";

        if (!(cin >> choice)) {
            clearInputBuffer();
            cerr << "Ошибка ввода! Попробуйте снова.\n";
            continue;
        }

        try {
            switch(choice) {
                case 1:
                    testStack<DateTime>();
                    break;
                case 2:
                    testStack<DateTimeWithTimeZone>();
                    break;
                case 3:
                    testStack<Timer>();
                    break;
                case 4:
                    testTimer();
                    break;
                case 5:
                    testTimeZone();
                    break;
                case 0:
                    return 0;
                default:
                    cout << "Неверный выбор!\n";
                    clearInputBuffer();
            }
        } catch(const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
            clearInputBuffer();
        }
    }
}


/*#include "datetime.h"
#include <iostream>
#include <iomanip>
#include <clocale>
#include <chrono>
#include <limits>
#include <stdexcept>
#include <fstream>
#include <vector>

using namespace std;

// Функции для проверки валидности временных зон
bool isTimeZoneValid(const string& tz) {
    try {
        std::chrono::locate_zone(tz);
        return true;
    } catch (...) {
        return false;
    }
}

bool isValidUTCOffset(const string& tz) {
    if (tz.size() < 4 || tz.size() > 9) return false;
    if (tz.substr(0, 3) != "UTC") return false;

    if (tz[3] == '+' || tz[3] == '-') {
        size_t colon_pos = tz.find(':');
        if (colon_pos != string::npos) {
            if (tz.size() != 9) return false;
            string hours = tz.substr(4, 2);
            string minutes = tz.substr(7, 2);
            if (!isdigit(hours[0]) || !isdigit(hours[1]) || !isdigit(minutes[0]) || !isdigit(minutes[1]))
                return false;
            int h = stoi(hours);
            int m = stoi(minutes);
            return (h >= 0 && h <= 23 && m >= 0 && m <= 59);
        } else {
            string hour_part = tz.substr(4);
            if (hour_part.empty()) return false;
            for (char c : hour_part) if (!isdigit(c)) return false;
            int h = stoi(hour_part);
            return (h >= 0 && h <= 23);
        }
    }
    return false;
}

// Функции для ввода данных с проверками
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

Date inputDate() {
    int d, m, y;
    while (true) {
        cout << "Введите дату (день месяц год через пробел): ";
        if (!(cin >> d >> m >> y)) {
            clearInputBuffer();
            cerr << "Ошибка ввода! Попробуйте снова.\n";
            continue;
        }
        try {
            return Date(d, m, y);
        } catch (const char* e) {
            cerr << "Ошибка: " << e << ". Попробуйте снова.\n";
            clearInputBuffer();
        }
    }
}

Time inputTime() {
    int h, min, s;
    while (true) {
        cout << "Введите время (часы минуты секунды через пробел): ";
        if (!(cin >> h >> min >> s)) {
            clearInputBuffer();
            cerr << "Ошибка ввода! Попробуйте снова.\n";
            continue;
        }
        try {
            return Time(h, min, s);
        } catch (const char* e) {
            cerr << "Ошибка: " << e << ". Попробуйте снова.\n";
            clearInputBuffer();
        }
    }
}

string inputTimeZone() {
    string tz;
    while (true) {
        cout << "Введите часовой пояс (например Europe/Moscow, UTC+3): ";
        cin >> tz;
        if (isTimeZoneValid(tz) || isValidUTCOffset(tz)) {
            return tz;
        }
        cerr << "Некорректный часовой пояс. Попробуйте снова.\n";
    }
}

// Шаблонная функция для тестирования стека DateTime
void testDateTimeStack() {
    Stack<DateTime> stack;
    int choice;

    while (true) {
        cout << "\n=== Тестирование стека DateTime ==="
             << "\nТекущий размер стека: " << stack.getSize()
             << "\n1. Добавить элемент (push)"
             << "\n2. Извлечь элемент (pop)"
             << "\n3. Вставить элемент по индексу"
             << "\n4. Удалить элемент по индексу"
             << "\n5. Найти элемент"
             << "\n6. Показать все элементы"
             << "\n7. Проверить пустоту стека"
             << "\n0. Вернуться"
             << "\nВыбор: ";

        cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    cout << "Введите данные для элемента:\n";
                    DateTime* item = new DateTime(inputDate(), inputTime());
                    stack.push(item);
                    cout << "Элемент добавлен.\n";
                    break;
                }
                case 2: {
                    DateTime* item = stack.pop();
                    if (item) {
                        cout << "Извлеченный элемент: " << *item << endl;
                        delete item;
                    } else {
                        cout << "Стек пуст.\n";
                    }
                    break;
                }
                case 3: {
                    int index;
                    cout << "Введите индекс для вставки: ";
                    cin >> index;
                    cout << "Введите данные для элемента:\n";
                    DateTime* item = new DateTime(inputDate(), inputTime());
                    stack.insert(index, item);
                    cout << "Элемент вставлен.\n";
                    break;
                }
                case 4: {
                    int index;
                    cout << "Введите индекс для удаления: ";
                    cin >> index;
                    stack.removeAt(index);
                    cout << "Элемент удален.\n";
                    break;
                }
                case 5: {
                    cout << "Введите данные для поиска:\n";
                    DateTime item(inputDate(), inputTime());
                    int index = stack.find(item);
                    if (index != -1) {
                        cout << "Элемент найден на позиции: " << index << endl;
                    } else {
                        cout << "Элемент не найден.\n";
                    }
                    break;
                }
                case 6: {
                    cout << "Элементы стека:\n";
                    stack.display();
                    break;
                }
                case 7: {
                    cout << "Стек " << (stack.isEmpty() ? "пуст" : "не пуст") << endl;
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Неверный выбор!\n";
            }
        } catch (const char* e) {
            cerr << "Ошибка: " << e << endl;
            clearInputBuffer();
        } catch (const exception& e) {
            cerr << "Исключение: " << e.what() << endl;
            clearInputBuffer();
        }
    }
}

// Функция для тестирования стека DateTimeWithTimeZone
void testDateTimeWithTimeZoneStack() {
    Stack<DateTimeWithTimeZone> stack;
    int choice;

    while (true) {
        cout << "\n=== Тестирование стека DateTimeWithTimeZone ==="
             << "\nТекущий размер стека: " << stack.getSize()
             << "\n1. Добавить элемент (push)"
             << "\n2. Извлечь элемент (pop)"
             << "\n3. Вставить элемент по индексу"
             << "\n4. Удалить элемент по индексу"
             << "\n5. Найти элемент"
             << "\n6. Показать все элементы"
             << "\n7. Проверить пустоту стека"
             << "\n0. Вернуться"
             << "\nВыбор: ";

        cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    cout << "Введите данные для элемента:\n";
                    DateTimeWithTimeZone* item = new DateTimeWithTimeZone(
                        inputDate(), inputTime(), inputTimeZone());
                    stack.push(item);
                    cout << "Элемент добавлен.\n";
                    break;
                }
                case 2: {
                    DateTimeWithTimeZone* item = stack.pop();
                    if (item) {
                        cout << "Извлеченный элемент: " << *item << endl;
                        delete item;
                    } else {
                        cout << "Стек пуст.\n";
                    }
                    break;
                }
                case 3: {
                    int index;
                    cout << "Введите индекс для вставки: ";
                    cin >> index;
                    cout << "Введите данные для элемента:\n";
                    DateTimeWithTimeZone* item = new DateTimeWithTimeZone(
                        inputDate(), inputTime(), inputTimeZone());
                    stack.insert(index, item);
                    cout << "Элемент вставлен.\n";
                    break;
                }
                case 4: {
                    int index;
                    cout << "Введите индекс для удаления: ";
                    cin >> index;
                    stack.removeAt(index);
                    cout << "Элемент удален.\n";
                    break;
                }
                case 5: {
                    cout << "Введите данные для поиска:\n";
                    DateTimeWithTimeZone item(
                        inputDate(), inputTime(), inputTimeZone());
                    int index = stack.find(item);
                    if (index != -1) {
                        cout << "Элемент найден на позиции: " << index << endl;
                    } else {
                        cout << "Элемент не найден.\n";
                    }
                    break;
                }
                case 6: {
                    cout << "Элементы стека:\n";
                    stack.display();
                    break;
                }
                case 7: {
                    cout << "Стек " << (stack.isEmpty() ? "пуст" : "не пуст") << endl;
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Неверный выбор!\n";
            }
        } catch (const char* e) {
            cerr << "Ошибка: " << e << endl;
            clearInputBuffer();
        } catch (const exception& e) {
            cerr << "Исключение: " << e.what() << endl;
            clearInputBuffer();
        }
    }
}

// Функция для тестирования стека Timer
void testTimerStack() {
    Stack<Timer> stack;
    int choice;

    while (true) {
        cout << "\n=== Тестирование стека Timer ==="
             << "\nТекущий размер стека: " << stack.getSize()
             << "\n1. Добавить элемент (push)"
             << "\n2. Извлечь элемент (pop)"
             << "\n3. Вставить элемент по индексу"
             << "\n4. Удалить элемент по индексу"
             << "\n5. Найти элемент"
             << "\n6. Показать все элементы"
             << "\n7. Проверить пустоту стека"
             << "\n0. Вернуться"
             << "\nВыбор: ";

        cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    cout << "Введите данные для элемента:\n";
                    Timer* item = new Timer(inputDate(), inputTime(), false);
                    stack.push(item);
                    cout << "Элемент добавлен.\n";
                    break;
                }
                case 2: {
                    Timer* item = stack.pop();
                    if (item) {
                        cout << "Извлеченный элемент: " << *item << endl;
                        delete item;
                    } else {
                        cout << "Стек пуст.\n";
                    }
                    break;
                }
                case 3: {
                    int index;
                    cout << "Введите индекс для вставки: ";
                    cin >> index;
                    cout << "Введите данные для элемента:\n";
                    Timer* item = new Timer(inputDate(), inputTime(), false);
                    stack.insert(index, item);
                    cout << "Элемент вставлен.\n";
                    break;
                }
                case 4: {
                    int index;
                    cout << "Введите индекс для удаления: ";
                    cin >> index;
                    stack.removeAt(index);
                    cout << "Элемент удален.\n";
                    break;
                }
                case 5: {
                    cout << "Введите данные для поиска:\n";
                    Timer item(inputDate(), inputTime(), false);
                    int index = stack.find(item);
                    if (index != -1) {
                        cout << "Элемент найден на позиции: " << index << endl;
                    } else {
                        cout << "Элемент не найден.\n";
                    }
                    break;
                }
                case 6: {
                    cout << "Элементы стека:\n";
                    stack.display();
                    break;
                }
                case 7: {
                    cout << "Стек " << (stack.isEmpty() ? "пуст" : "не пуст") << endl;
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Неверный выбор!\n";
            }
        } catch (const char* e) {
            cerr << "Ошибка: " << e << endl;
            clearInputBuffer();
        } catch (const exception& e) {
            cerr << "Исключение: " << e.what() << endl;
            clearInputBuffer();
        }
    }
}

// Тестирование таймера
void testTimer() {
    cout << "\n=== Тестирование Таймера ===\n";
    Timer timer;
    int choice;

    while(true) {
        cout << "\n1. Запустить таймер\n"
             << "2. Остановить таймер\n"
             << "3. Сбросить таймер\n"
             << "4. Получить прошедшее время\n"
             << "5. Ожидание\n"
             << "0. Выход\n"
             << "Выбор: ";
        cin >> choice;

        try {
            switch(choice) {
                case 1:
                    timer.StartTimer();
                    cout << "Таймер запущен в: " << timer << endl;
                    break;
                case 2:
                    timer.StopTimer();
                    cout << "Таймер остановлен в: " << timer << endl;
                    break;
                case 3:
                    timer.ResetTimer();
                    cout << "Таймер сброшен до: " << timer << endl;
                    break;
                case 4: {
                    int seconds = timer.GetSeconds();
                    int ms = timer.GetMilliseconds();
                    cout << "Прошло времени: " << seconds << " секунд (" << ms << " мс)\n";
                    cout << "Текущее время: " << timer << endl;
                    break;
                }
                case 5: {
                    int sec;
                    cout << "Введите секунды для ожидания: ";
                    cin >> sec;
                    timer.WaitTimer(sec);
                    cout << "Ожидание " << sec << " секунд завершено\n";
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Неверный выбор!\n";
            }
        } catch(const char* e) {
            cerr << "Ошибка: " << e << endl;
        } catch(const exception& e) {
            cerr << "Исключение: " << e.what() << endl;
        }
    }
}

// Тестирование часовых поясов
void testTimeZone() {
    cout << "\n=== Тестирование Часовых поясов ===\n";
    DateTimeWithTimeZone dtz;
    string tz;
    int choice;

    while(true) {
        cout << "\nТекущий часовой пояс: " << dtz.getTimeZone() << endl;
        cout << "1. Установить часовой пояс\n"
             << "2. Показать текущее время\n"
             << "0. Выход\n"
             << "Выбор: ";
        cin >> choice;

        try {
            switch(choice) {
                case 1: {
                    bool valid = false;
                    while (!valid) {
                        cout << "Введите часовой пояс (например Europe/Moscow, UTC+3): ";
                        cin >> tz;
                        if (isTimeZoneValid(tz) || isValidUTCOffset(tz)) {
                            dtz.setTimeZone(tz);
                            cout << "Часовой пояс установлен на: " << dtz.getTimeZone() << endl;
                            valid = true;
                        } else {
                            cout << "Некорректный часовой пояс. Попробуйте снова.\n";
                        }
                    }
                    break;
                }
                case 2: {
                    auto zt = dtz.getCurrentTime();
                    auto now = std::chrono::system_clock::now();
                    auto local_time = std::chrono::current_zone()->to_local(now);
                    cout << "Время в выбранном поясе: " << std::format("{:%d.%m.%Y %H:%M:%S}", zt.get_local_time()) << endl;
                    break;
                }
                case 0:
                    return;
                default:
                    cout << "Неверный выбор!\n";
            }
        } catch(const char* e) {
            cerr << "Ошибка: " << e << endl;
        } catch(const exception& e) {
            cerr << "Исключение: " << e.what() << endl;
        }
    }
}

// Главное меню
int main() {
    setlocale(LC_ALL, "Russian");
    int choice;

    while(true) {
        cout << "\n=== Главное меню ==="
             << "\n1. Тестирование стека DateTime"
             << "\n2. Тестирование стека DateTimeWithTimeZone"
             << "\n3. Тестирование стека Timer"
             << "\n4. Тестирование таймера"
             << "\n5. Тестирование часовых поясов"
             << "\n0. Выход"
             << "\nВыбор: ";
        cin >> choice;

        switch(choice) {
            case 1:
                testDateTimeStack();
                break;
            case 2:
                testDateTimeWithTimeZoneStack();
                break;
            case 3:
                testTimerStack();
                break;
            case 4:
                testTimer();
                break;
            case 5:
                testTimeZone();
                break;
            case 0:
                return 0;
            default:
                cout << "Неверный выбор!\n";
        }
    }
}
*/
