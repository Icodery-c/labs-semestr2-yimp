#include "datetime.h"
#include <iostream>
#include <iomanip>
#include <clocale>
#include <chrono>
#include <limits>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <filesystem>


namespace fs = std::filesystem;
using namespace std;


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
            try {
                throw FormatException("Ожидается формат ДД.ММ.ГГГГ");
            } catch (const DateTimeException& e) {
                cerr << "Ошибка: " << e.what() << '\n';
            }
            continue;
        }
        try {
            return Date(d, m, y);
        } catch (const RangeException& e) {
            cerr << "Ошибка: " << e.what() << '\n';
        } catch (const DateTimeException& e) {
            cerr << "Ошибка даты: " << e.what() << '\n';
        } catch (...) {
            cerr << "Неизвестная ошибка даты.\n";
        }
        clearInputBuffer();
    }
}

Time inputTime() {
    int h, min, s;
    char sep1, sep2;
    while (true) {
        cout << "Введите время в формате ЧЧ:ММ:СС: ";
        if (!(cin >> h >> sep1 >> min >> sep2 >> s) || sep1 != ':' || sep2 != ':') {
            clearInputBuffer();
            try {
                throw FormatException("Ожидается формат ЧЧ:ММ:СС");
            } catch (const DateTimeException& e) {
                cerr << "Ошибка: " << e.what() << '\n';
            }
            continue;
        }
        try {
            return Time(h, min, s);
        } catch (const RangeException& e) {
            cerr << "Ошибка: " << e.what() << '\n';
        } catch (const DateTimeException& e) {
            cerr << "Ошибка времени: " << e.what() << '\n';
        } catch (...) {
            cerr << "Неизвестная ошибка времени.\n";
        }
        clearInputBuffer();
    }
}

string inputTimeZone() {
    string tz;
    while (true) {
        cout << "Введите часовой пояс (например Europe/Moscow, UTC+03:00): ";
        cin >> tz;
        try {
            if (isTimeZoneValid(tz) || isValidUTCOffset(tz)) {
                return tz;
            } else {
                throw FormatException("Некорректный формат часового пояса");
            }
        } catch (const DateTimeException& e) {
            cerr << "Ошибка: " << e.what() << '\n';
        }
        clearInputBuffer();
      }
}

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
                    T* item = nullptr;
                    try {
                        cout << "Введите данные для элемента:\n";
                        if constexpr (is_same_v<T, DateTime>) {
                            item = new T(inputDate(), inputTime());
                        } else if constexpr (is_same_v<T, DateTimeWithTimeZone>) {
                            item = new T(inputDate(), inputTime(), inputTimeZone());
                        } else if constexpr (is_same_v<T, Timer>) {
                            item = new T(inputDate(), inputTime(), false);
                        }
                        stack.push(item);
                        cout << "Элемент добавлен.\n";
                    } catch (const RangeException& e) {
                        delete item;
                        cerr << "RangeException: " << e.what() << endl;
                    } catch (const FormatException& e) {
                        delete item;
                        cerr << "FormatException: " << e.what() << endl;
                    }
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

                    T* item = nullptr;
                    try {
                        cout << "Введите данные для элемента:\n";
                        if constexpr (is_same_v<T, DateTime>) {
                            item = new T(inputDate(), inputTime());
                        } else if constexpr (is_same_v<T, DateTimeWithTimeZone>) {
                            item = new T(inputDate(), inputTime(), inputTimeZone());
                        } else if constexpr (is_same_v<T, Timer>) {
                            item = new T(inputDate(), inputTime(), false);
                        }
                        stack.insert(index, item);
                        cout << "Элемент вставлен.\n";
                    } catch (const out_of_range& e) {
                        delete item;
                        cerr << "Ошибка диапазона: " << e.what() << endl;
                    } catch (const RangeException& e) {
                        delete item;
                        cerr << "RangeException: " << e.what() << endl;
                    } catch (const FormatException& e) {
                        delete item;
                        cerr << "FormatException: " << e.what() << endl;
                    }
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
                    try {
                        stack.removeAt(index);
                        cout << "Элемент удален.\n";
                    } catch (const out_of_range& e) {
                        cerr << "Ошибка диапазона: " << e.what() << endl;
                    }
                    break;
                }
                case 5: {
                    try {
                        cout << "Введите данные для поиска:\n";
                        T item = []() {
                            if constexpr (is_same_v<T, DateTime>) {
                                return T(inputDate(), inputTime());
                            } else if constexpr (is_same_v<T, DateTimeWithTimeZone>) {
                                return T(inputDate(), inputTime(), inputTimeZone());
                            } else if constexpr (is_same_v<T, Timer>) {
                                return T(inputDate(), inputTime(), false);
                            }
                        }();

                        int index = stack.find(item);
                        if (index != -1) {
                            cout << "Элемент найден на позиции: " << index << endl;
                        } else {
                            cout << "Элемент не найден.\n";
                        }
                    } catch (const exception& e) {
                        cerr << "Ошибка при поиске: " << e.what() << endl;
                    }
                    break;
                }
                case 6: {
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
                    cerr << "Неверный выбор!\n";
                    clearInputBuffer();
            }
        } catch (const exception& e) {
            cerr << "Необработанное исключение: " << e.what() << endl;
            clearInputBuffer();
        }
    }
}

void testTimer() {
    cout << "\n=== Тестирование Таймера ===\n";
    Timer timer;
    int choice;

    while (true) {
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
            switch (choice) {
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
                    if (!(cin >> sec) || sec < 0) {
                        clearInputBuffer();
                        throw RangeException("Некорректное значение секунд!");
                    }
                    timer.WaitTimer(sec);
                    cout << "Ожидание " << sec << " секунд завершено\n";
                    break;
                }
                case 0:
                    return;
                default:
                    cerr << "Неверный выбор!\n";
                    clearInputBuffer();
            }
        } catch (const RangeException& e) {
            cerr << "RangeException: " << e.what() << endl;
        } catch (const char* e) {
            cerr << "Ошибка: " << e << endl;
        } catch (const exception& e) {
            cerr << "Исключение: " << e.what() << endl;
        }
    }
}

void testTimeZone() {
    cout << "\n=== Тестирование Часовых поясов ===\n";
    DateTimeWithTimeZone dtz;
    string tz;
    int choice;

    while (true) {
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
            switch (choice) {
                case 1: {
                    cout << "Введите часовой пояс (например Europe/Moscow, UTC+3): ";
                    cin >> tz;

                    if (!isTimeZoneValid(tz) && !isValidUTCOffset(tz)) {
                        throw FormatException("Недопустимый формат часового пояса!");
                    }

                    dtz.setTimeZone(tz);
                    cout << "Часовой пояс установлен на: " << dtz.getTimeZone() << endl;
                    break;
                }
                case 2: {
                    auto zt = dtz.getCurrentTime();
                    cout << "Время в выбранном поясе: "
                         << std::format("{:%d.%m.%Y %H:%M:%S}", zt.get_local_time()) << endl;
                    break;
                }
                case 0:
                    return;
                default:
                    cerr << "Неверный выбор!\n";
                    clearInputBuffer();
            }
        } catch (const FormatException& e) {
            cerr << "FormatException: " << e.what() << endl;
        } catch (const runtime_error& e) {
            cerr << "Ошибка времени: " << e.what() << endl;
        } catch (const char* e) {
            cerr << "Ошибка: " << e << endl;
        } catch (const exception& e) {
            cerr << "Исключение: " << e.what() << endl;
        }
    }
}

void testDateOperators() {

    cout << "\n=== Тестирование операторов Date ===\n";
    Date d1 = inputDate();
    Date d2 = inputDate();

    static bool textFileKnown = false;
    static bool binFileKnown  = false;

    int choice;
    while (true) {
        cout << "\nВыберите оператор для тестирования:\n"
             << "1. d1 + int (добавить дни)\n"
             << "2. d1 - int (вычесть дни)\n"
             << "3. d1 + d2 (сложить даты)\n"
             << "4. d1 - d2 (вычесть даты)\n"
             << "5. d1 += int\n"
             << "6. d1 -= int\n"
             << "7. Преобразование d1 и d2 в char*\n"
             << "8. Тест операторов ввода/вывода\n"
             << "9. Запись в файл и чтение\n"
             << "10. Запись в бинарный файл и чтение\n"
             << "0. Вернуться\n"
             << "Выбор: ";

        cin >> choice;
        if (cin.fail()) {
            clearInputBuffer();
            cerr << "Ошибка ввода! Попробуйте снова.\n";
            continue;
        }

        try {
            int days;
            Date result;
            switch (choice) {
                case 1:
                    cout << "Введите количество дней для добавления: ";
                    cin >> days;
                    result = d1 + days;
                    cout << d1.printDate() << " + " << days << " дней = " << result.printDate() << endl;
                    break;
                case 2:
                    cout << "Введите количество дней для вычитания: ";
                    cin >> days;
                    result = d1 - days;
                    cout << d1.printDate() << " - " << days << " дней = " << result.printDate() << endl;
                    break;
                case 3:
                    result = d1 + d2;
                    cout << d1.printDate() << " + " << d2.printDate() << " = " << result.printDate() << endl;
                    break;
                case 4:
                    result = d1 - d2;
                    cout << d1.printDate() << " - " << d2.printDate() << " = " << result.printDate() << endl;
                    break;
                case 5:
                    cout << "Введите количество дней для добавления: ";
                    cin >> days;
                    cout << "До: " << d1.printDate() << endl;
                    d1 += days;
                    cout << "После: " << d1.printDate() << endl;
                    break;
                case 6:
                    cout << "Введите количество дней для вычитания: ";
                    cin >> days;
                    cout << "До: " << d1.printDate() << endl;
                    d1 -= days;
                    cout << "После: " << d1.printDate() << endl;
                    break;
                case 7:
                    cout << "d1 как const char*: " << (const char*)d1 << endl;
                    cout << "d2 как const char*: " << (const char*)d2 << endl;
                    break;
                case 8: {
                    cout << "Тестирование операторов ввода/вывода:\n";
                    int count;
                    cout << "Сколько дат вы хотите ввести? ";
                    cin >> count;

                    vector<Date> dates;
                    for (int i = 0; i < count; ) {
                        cout << "Дата #" << i+1 << ": ";
                        Date temp;
                        try {
                            cin >> temp;
                            dates.push_back(temp);
                            i++;
                        } catch (const char* e) {
                            cerr << "Ошибка: " << e << endl;
                            clearInputBuffer();
                        }
                    }

                    cout << "\nВведенные даты:\n";
                    for (const auto& date : dates) {
                        cout << date << endl;
                    }
                    break;
                }

                case 9: {
                    fs::path filePath = "dates.txt";

                    // Если файла нет и это не первая запись — ошибка
                    if (!fs::exists(filePath) && textFileKnown) {
                        throw runtime_error("Файл был удалён или переименован. Запись невозможна.");
                    }

                    // Собираем новые даты
                    int count;
                    cout << "Сколько дат вы хотите записать в файл? ";
                    cin >> count;

                    vector<Date> dates;
                    for (int i = 0; i < count; ) {
                        cout << "Введите дату #" << i+1 << " (день/месяц/год): ";
                        Date temp;
                        try {
                            cin >> temp;
                            dates.push_back(temp);
                            i++;
                        } catch (const char* e) {
                            cerr << "Ошибка: " << e << endl;
                            clearInputBuffer();
                        }
                    }

                    // Открываем (создаём при необходимости) и дописываем
                    ofstream out(filePath, ios::app);
                    if (!out) {
                        throw runtime_error("Не удалось открыть файл для записи.");
                    }
                    for (auto& dt : dates) {
                        out << dt << endl;
                    }
                    out.close();

                    textFileKnown = true;
                    cout << "Данные записаны в " << filePath << endl;
                    break;
                }

                case 10: {
                    fs::path binFilePath = "dates.bin";

                    // Если файла нет и это не первая запись — ошибка
                    if (!fs::exists(binFilePath) && binFileKnown) {
                        throw runtime_error("Бинарный файл был удалён или переименован. Запись невозможна.");
                    }

                    // Собираем новые даты
                    int count;
                    cout << "Сколько дат вы хотите записать в бинарный файл? ";
                    cin >> count;

                    vector<Date> dates;
                    for (int i = 0; i < count; ) {
                        cout << "Введите дату #" << i+1 << " (день/месяц/год): ";
                        Date temp;
                        try {
                            cin >> temp;
                            dates.push_back(temp);
                            i++;
                        } catch (const char* e) {
                            cerr << "Ошибка: " << e << endl;
                            clearInputBuffer();
                        }
                    }

                    // Открываем (создаём при необходимости) и дописываем
                    ofstream out(binFilePath, ios::binary | ios::app);
                    if (!out) {
                        throw runtime_error("Не удалось открыть бинарный файл для записи.");
                    }

                    size_t sz = dates.size();
                    out.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
                    for (auto& dt : dates) {
                        int d = dt.getDay(), m = dt.getMonth(), y = dt.getYear();
                        out.write(reinterpret_cast<const char*>(&d), sizeof(d));
                        out.write(reinterpret_cast<const char*>(&m), sizeof(m));
                        out.write(reinterpret_cast<const char*>(&y), sizeof(y));
                    }
                    out.close();

                    binFileKnown = true;
                    cout << "Данные записаны в " << binFilePath << endl;
                    break;
                }

                case 0:
                    return;

                default:
                    cerr << "Неверный выбор! Попробуйте снова.\n";
            }
        } catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
            clearInputBuffer();
        }
    }
}

void testTimeOperators() {
    using namespace std;
    cout << "\n=== Тестирование операторов Time ===\n";
    Time t1 = inputTime();
    Time t2 = inputTime();

    // Статические флаги, чтобы помнить, что файл уже создавался
    static bool textTimeKnown = false;
    static bool binTimeKnown  = false;

    int choice;
    while (true) {
        cout << "\nВыберите оператор для тестирования:\n"
             << "1. t1 + int (добавить часы)\n"
             << "2. t1 - int (вычесть часы)\n"
             << "3. t1 + t2 (сложить время)\n"
             << "4. t1 - t2 (вычесть время)\n"
             << "5. t1 += int\n"
             << "6. t1 -= int\n"
             << "7. Преобразование t1 and t2 в char*\n"
             << "8. Тест операторов ввода/вывода\n"
             << "9. Запись в файл и чтение\n"
             << "10. Запись в бинарный файл и чтение\n"
             << "0. Вернуться\n"
             << "Выбор: ";

        cin >> choice;
        if (cin.fail()) {
            clearInputBuffer();
            cerr << "Ошибка ввода! Попробуйте снова.\n";
            continue;
        }

        try {
            int hours;
            Time result;

            switch (choice) {
                case 1:
                    cout << "Введите количество часов для добавления: ";
                    cin >> hours;
                    result = t1 + hours;
                    cout << t1.printTime() << " + " << hours << " часов = " << result.printTime() << endl;
                    break;
                case 2:
                    cout << "Введите количество часов для вычитания: ";
                    cin >> hours;
                    result = t1 - hours;
                    cout << t1.printTime() << " - " << hours << " часов = " << result.printTime() << endl;
                    break;
                case 3:
                    result = t1 + t2;
                    cout << t1.printTime() << " + " << t2.printTime() << " = " << result.printTime() << endl;
                    break;
                case 4:
                    result = t1 - t2;
                    cout << t1.printTime() << " - " << t2.printTime() << " = " << result.printTime() << endl;
                    break;
                case 5:
                    cout << "Введите количество часов для добавления: ";
                    cin >> hours;
                    cout << "До: " << t1.printTime() << endl;
                    t1 += hours;
                    cout << "После: " << t1.printTime() << endl;
                    break;
                case 6:
                    cout << "Введите количество часов для вычитания: ";
                    cin >> hours;
                    cout << "До: " << t1.printTime() << endl;
                    t1 -= hours;
                    cout << "После: " << t1.printTime() << endl;
                    break;
                case 7:
                    cout << "t1 как const char*: " << (const char*)t1 << endl;
                    cout << "t2 как const char*: " << (const char*)t2 << endl;
                    break;

                case 8: {
                    cout << "Тестирование операторов ввода/вывода:\n";
                    int count;
                    cout << "Сколько значений времени вы хотите ввести? ";
                    cin >> count;

                    vector<Time> times;
                    for (int i = 0; i < count; ) {
                        cout << "Время #" << i+1 << ": ";
                        Time temp;
                        try {
                            cin >> temp;
                            times.push_back(temp);
                            i++;
                        } catch (const char* e) {
                            cerr << "Ошибка: " << e << endl;
                            clearInputBuffer();
                        }
                    }

                    cout << "\nВведённые значения времени:\n";
                    for (auto& tm : times) {
                        cout << tm << endl;
                    }
                    break;
                }

                case 9: {
                    fs::path filePath = "times.txt";

                    // Если файл отсутствует и это не первая запись — бросаем исключение
                    if (!fs::exists(filePath) && textTimeKnown) {
                        throw runtime_error("Файл times.txt был удалён или переименован. Запись невозможна.");
                    }

                    // Ввод новых значений
                    int count;
                    cout << "Сколько значений времени вы хотите записать в файл? ";
                    cin >> count;

                    vector<Time> times;
                    for (int i = 0; i < count; ) {
                        cout << "Введите время #" << i+1 << " (часы минуты секунды): ";
                        Time temp;
                        try {
                            cin >> temp;
                            times.push_back(temp);
                            i++;
                        } catch (const char* e) {
                            cerr << "Ошибка: " << e << " Пожалуйста, введите время снова.\n";
                            clearInputBuffer();
                        }
                    }

                    // Открываем (или создаём) файл в режиме append
                    ofstream out("times.txt", ios::app);
                    if (!out.is_open()) {
                        throw runtime_error("Не удалось открыть times.txt для записи");
                    }
                    for (auto& tm : times) {
                        out << tm << endl;
                    }
                    out.close();

                    textTimeKnown = true;
                    cout << "Данные записаны в times.txt\n";
                    break;
                }

                case 10: {
                    fs::path binFilePath = "times.bin";

                    // Если файл отсутствует и это не первая запись — бросаем исключение
                    if (!fs::exists(binFilePath) && binTimeKnown) {
                        throw runtime_error("Бинарный файл times.bin был удалён или переименован. Запись невозможна.");
                    }

                    // Ввод новых значений
                    int count;
                    cout << "Сколько значений времени вы хотите записать в бинарный файл? ";
                    cin >> count;

                    vector<Time> times;
                    for (int i = 0; i < count; ) {
                        cout << "Введите время #" << i+1 << " (часы минуты секунды): ";
                        Time temp;
                        try {
                            cin >> temp;
                            times.push_back(temp);
                            i++;
                        } catch (const char* e) {
                            cerr << "Ошибка: " << e << " Пожалуйста, введите время снова.\n";
                            clearInputBuffer();
                        }
                    }

                    // Открываем (или создаём) бинарный файл в режиме append
                    ofstream out("times.bin", ios::binary | ios::app);
                    if (!out.is_open()) {
                        throw runtime_error("Не удалось открыть times.bin для записи");
                    }

                    size_t sz = times.size();
                    out.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
                    for (auto& tm : times) {
                        int h = tm.getHour(), m = tm.getMinute(), s = tm.getSecond();
                        out.write(reinterpret_cast<const char*>(&h), sizeof(h));
                        out.write(reinterpret_cast<const char*>(&m), sizeof(m));
                        out.write(reinterpret_cast<const char*>(&s), sizeof(s));
                    }
                    out.close();

                    binTimeKnown = true;
                    cout << "Данные записаны в times.bin\n";
                    break;
                }

                case 0:
                    return;

                default:
                    cerr << "Неверный выбор! Попробуйте снова.\n";
            }
        } catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
            clearInputBuffer();
        }
    }
}

void testDateTimeOperators() {
    cout << "\n=== Тестирование операторов DateTime ===\n";
    cout << "Введите первую дату и время:\n";
    DateTime dt1(inputDate(), inputTime());

    cout << "\nВведите вторую дату и время:\n";
    DateTime dt2(inputDate(), inputTime());

    static bool textDateTimeKnown = false;
    static bool binDateTimeKnown  = false;

    int choice;
    while (true) {
        cout << "\nВыберите оператор для тестирования:\n"
             << "1. dt1 + int (добавить дни)\n"
             << "2. dt1 - int (вычесть дни)\n"
             << "3. dt1 + dt2 (сложить даты и время)\n"
             << "4. dt1 - dt2 (вычесть даты и время)\n"
             << "5. dt1 += int\n"
             << "6. dt1 -= int\n"
             << "7. Преобразование dt1 and dt2 в char*\n"
             << "8. Тест операторов ввода/вывода\n"
             << "9. Запись в файл и чтение\n"
             << "10. Запись в бинарный файл и чтение\n"
             << "0. Вернуться\n"
             << "Выбор: ";

        cin >> choice;
        if (cin.fail()) {
            clearInputBuffer();
            cerr << "Ошибка ввода! Попробуйте снова.\n";
            continue;
        }

        try {
            int days;
            DateTime result = dt1; // Инициализируем копией dt1
            switch (choice) {
                case 1:
                    cout << "Введите количество дней для добавления: ";
                    cin >> days;
                    result = dt1 + days;
                    cout << dt1.printDateTime() << " + " << days << " дней = " << result.printDateTime() << endl;
                    break;
                case 2:
                    cout << "Введите количество дней для вычитания: ";
                    cin >> days;
                    result = dt1 - days;
                    cout << dt1.printDateTime() << " - " << days << " дней = " << result.printDateTime() << endl;
                    break;
                case 3:
                    result = dt1 + dt2;
                    cout << dt1.printDateTime() << " + " << dt2.printDateTime() << " = " << result.printDateTime() << endl;
                    break;
                case 4:
                    result = dt1 - dt2;
                    cout << dt1.printDateTime() << " - " << dt2.printDateTime() << " = " << result.printDateTime() << endl;
                    break;
                case 5:
                    cout << "Введите количество дней для добавления: ";
                    cin >> days;
                    cout << "До: " << dt1.printDateTime() << endl;
                    dt1 += days;
                    cout << "После: " << dt1.printDateTime() << endl;
                    break;
                case 6:
                    cout << "Введите количество дней для вычитания: ";
                    cin >> days;
                    cout << "До: " << dt1.printDateTime() << endl;
                    dt1 -= days;
                    cout << "После: " << dt1.printDateTime() << endl;
                    break;
                case 7:
                    cout << "dt1 как const char*: " << (const char*)dt1 << endl;
                    cout << "dt2 как const char*: " << (const char*)dt2 << endl;
                    break;
                    case 8: {
        cout << "Тестирование операторов ввода/вывода:\n";
        int count;
        cout << "Сколько значений DateTime вы хотите ввести? ";
        cin >> count;

        vector<DateTime> datetimes;
        for (int i = 0; i < count; ) {
            cout << "DateTime #" << i+1 << ":\n";
            try {
                cout << "Введите дату:\n";
                Date d = inputDate();
                cout << "Введите время:\n";
                Time t = inputTime();
                datetimes.push_back(DateTime(d, t));
                i++;
            }
            catch (const char* e) {
                cerr << "Ошибка: " << e << endl;
                clearInputBuffer();
            }
        }

        cout << "\nВведенные значения DateTime:\n";
        for (const auto& dt : datetimes) {
            cout << dt << endl;
        }
        break;
    }
    case 9: {
    fs::path filePath = "datetimes.txt";

    // Проверка существования файла, если ранее он был создан
    if (!fs::exists(filePath) && textDateTimeKnown) {
        throw runtime_error("Файл datetimes.txt был удалён или переименован. Запись невозможна.");
    }

    int count;
    cout << "Сколько значений DateTime вы хотите записать в файл? ";
    cin >> count;

    vector<DateTime> datetimes;
    for (int i = 0; i < count; ) {
        try {
            cout << "Введите DateTime #" << i+1 << ":\n";
            Date d = inputDate();
            Time t = inputTime();
            datetimes.push_back(DateTime(d, t));
            i++;
        } catch (const char* e) {
            cerr << "Ошибка: " << e << " Пожалуйста, введите данные снова.\n";
            clearInputBuffer();
        }
    }

    // Запись в файл в режиме добавления
    ofstream out("datetimes.txt", ios::app);
    if (!out.is_open()) {
        throw runtime_error("Не удалось открыть datetimes.txt для записи");
    }
    for (const auto& dt : datetimes) {
        out << dt << endl;
    }
    out.close();

    textDateTimeKnown = true;
    cout << "Данные записаны в datetimes.txt\n";
    break;
}
case 10: {
  fs::path binFilePath = "datetimes.bin";

  // Проверка существования файла, если ранее он был создан
  if (!fs::exists(binFilePath) && binDateTimeKnown) {
      throw runtime_error("Бинарный файл datetimes.bin был удалён или переименован. Запись невозможна.");
  }

  int count;
  cout << "Сколько значений DateTime вы хотите записать в бинарный файл? ";
  cin >> count;

  vector<DateTime> datetimes;
  for (int i = 0; i < count; ) {
      try {
          cout << "Введите DateTime #" << i+1 << ":\n";
          Date d = inputDate();
          Time t = inputTime();
          datetimes.push_back(DateTime(d, t));
          i++;
      } catch (const char* e) {
          cerr << "Ошибка: " << e << " Пожалуйста, введите данные снова.\n";
          clearInputBuffer();
      }
  }

  // Запись в бинарный файл в режиме добавления
  ofstream out("datetimes.bin", ios::binary | ios::app);
  if (!out.is_open()) {
      throw runtime_error("Не удалось открыть datetimes.bin для записи");
  }

  size_t sz = datetimes.size();
  out.write(reinterpret_cast<const char*>(&sz), sizeof(sz));
  for (const auto& dt : datetimes) {
      int y = dt.getDate().getYear();
      int m = dt.getDate().getMonth();
      int d = dt.getDate().getDay();
      int h = dt.getTime().getHour();
      int min = dt.getTime().getMinute();
      int s = dt.getTime().getSecond();

      out.write(reinterpret_cast<const char*>(&y), sizeof(y));
      out.write(reinterpret_cast<const char*>(&m), sizeof(m));
      out.write(reinterpret_cast<const char*>(&d), sizeof(d));
      out.write(reinterpret_cast<const char*>(&h), sizeof(h));
      out.write(reinterpret_cast<const char*>(&min), sizeof(min));
      out.write(reinterpret_cast<const char*>(&s), sizeof(s));
  }
  out.close();

  binDateTimeKnown = true;
  cout << "Данные записаны в datetimes.bin\n";
  break;
}

  case 0:
    return;

default:
    cerr << "Неверный выбор! Попробуйте снова.\n";
}
} catch (const exception& e) {
cerr << "Ошибка: " << e.what() << endl;
clearInputBuffer();
}
}



}

void showDateTimeMenu(DateTime& dt) {
    int choice;
    while (true) {
        cout << "\nТекущие значения: " << dt.printDateTime() << endl;
        cout << "Главное меню:\n"
             << "\n1. Работа с датой"
             << "\n2. Работа со временем"
             << "\n3. Тест операторов Date"
             << "\n4. Тест операторов Time"
             << "\n5. Тест операторов DateTime"
             << "\n6. Тестирование стека DateTime"
             << "\n7. Тестирование стека DateTimeWithTimeZone"
             << "\n8. Тестирование стека Timer"
             << "\n9. Тестирование таймера"
             << "\n10. Тестирование часовых поясов"
             << "\n0. Выход\n"
             << "Выбор: ";

        cin >> choice;
        if (cin.fail()) {
            clearInputBuffer();
            cerr << "Ошибка ввода! Попробуйте снова.\n";
            continue;
        }

        try {
            switch (choice) {
                case 1: {
                    // Меню работы с датой
                    int dateChoice;
                    while (true) {
                        cout << "\nТекущая дата: " << dt.getDate().printDate() << endl;
                        cout << "Операции с датой:\n"
                             << "1. Увеличить день\n"
                             << "2. Уменьшить день\n"
                             << "3. Увеличить месяц\n"
                             << "4. Уменьшить месяц\n"
                             << "5. Увеличить год\n"
                             << "6. Уменьшить год\n"
                             << "7. Установить новую дату\n"
                             << "0. Вернуться\n"
                             << "Выбор: ";

                        cin >> dateChoice;
                        if (cin.fail()) {
                            clearInputBuffer();
                            cerr << "Ошибка ввода! Попробуйте снова.\n";
                            continue;
                        }

                        try {
                            int value;
                            switch (dateChoice) {
                                case 1:
                                    cout << "На сколько дней увеличить? ";
                                    cin >> value;
                                    dt.getDate().increaseDay(value);
                                    break;
                                case 2:
                                    cout << "На сколько дней уменьшить? ";
                                    cin >> value;
                                    dt.getDate().decreaseDay(value);
                                    break;
                                case 3:
                                    cout << "На сколько месяцев увеличить? ";
                                    cin >> value;
                                    dt.getDate().increaseMonth(value);
                                    break;
                                case 4:
                                    cout << "На сколько месяцев уменьшить? ";
                                    cin >> value;
                                    dt.getDate().decreaseMonth(value);
                                    break;
                                case 5:
                                    cout << "На сколько лет увеличить? ";
                                    cin >> value;
                                    dt.getDate().increaseYear(value);
                                    break;
                                case 6:
                                    cout << "На сколько лет уменьшить? ";
                                    cin >> value;
                                    dt.getDate().decreaseYear(value);
                                    break;
                                case 7:
                                    dt = DateTime(inputDate(), dt.getTime());
                                    break;
                                case 0:
                                    break;
                                default:
                                    cerr << "Неверный выбор! Попробуйте снова.\n";
                                    continue;
                            }
                            if (dateChoice == 0) break;
                        } catch (const char* e) {
                            cerr << "Ошибка: " << e << endl;
                            clearInputBuffer();
                        }
                    }
                    break;
                }
                case 2: {
                    // Меню работы с временем
                    int timeChoice;
                    while (true) {
                        cout << "\nТекущее время: " << dt.getTime().printTime() << endl;
                        cout << "Операции со временем:\n"
                             << "1. Увеличить часы\n"
                             << "2. Уменьшить часы\n"
                             << "3. Увеличить минуты\n"
                             << "4. Уменьшить минуты\n"
                             << "5. Увеличить секунды\n"
                             << "6. Уменьшить секунды\n"
                             << "7. Установить новое время\n"
                             << "0. Вернуться\n"
                             << "Выбор: ";

                        cin >> timeChoice;
                        if (cin.fail()) {
                            clearInputBuffer();
                            cerr << "Ошибка ввода! Попробуйте снова.\n";
                            continue;
                        }

                        try {
                            int value;
                            switch (timeChoice) {
                                case 1:
                                    cout << "На сколько часов увеличить? ";
                                    cin >> value;
                                    dt.increaseHour(value);
                                    break;
                                case 2:
                                    cout << "На сколько часов уменьшить? ";
                                    cin >> value;
                                    dt.decreaseHour(value);
                                    break;
                                case 3:
                                    cout << "На сколько минут увеличить? ";
                                    cin >> value;
                                    dt.increaseMinute(value);
                                    break;
                                case 4:
                                    cout << "На сколько минут уменьшить? ";
                                    cin >> value;
                                    dt.decreaseMinute(value);
                                    break;
                                case 5:
                                    cout << "На сколько секунд увеличить? ";
                                    cin >> value;
                                    dt.increaseSecond(value);
                                    break;
                                case 6:
                                    cout << "На сколько секунд уменьшить? ";
                                    cin >> value;
                                    dt.decreaseSecond(value);
                                    break;
                                case 7:
                                    dt = DateTime(dt.getDate(), inputTime());
                                    break;
                                case 0:
                                    break;
                                default:
                                    cerr << "Неверный выбор! Попробуйте снова.\n";
                                    continue;
                            }
                            if (timeChoice == 0) break;
                        } catch (const char* e) {
                            cerr << "Ошибка: " << e << endl;
                            clearInputBuffer();
                        }
                    }
                    break;
                }
                case 3:
                    testDateOperators();
                    break;
                case 4:
                    testTimeOperators();
                    break;
                case 5:
                    testDateTimeOperators();
                    break;
                case 6:
                  testStack<DateTime>();
                  break;
                case 7:
                  testStack<DateTimeWithTimeZone>();
                  break;
                case 8:
                  testStack<Timer>();
                  break;
                case 9:
                  testTimer();
                  break;
                case 10:
                  testTimeZone();
                  break;
                case 0:
                    cout << "\nФинальные значения: " << dt.printDateTime() << endl;
                    return;
                default:
                    cerr << "Неверный выбор! Попробуйте снова.\n";
                    clearInputBuffer();
            }
        }  catch(const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
            clearInputBuffer();
        }
    }
}


int main() {
    try {
        cout << "=== Программа работы с датой и временем ===\n\n";

        cout << "Введите начальную дату:\n";
        Date date = inputDate();

        cout << "\nВведите начальное время:\n";
        Time time = inputTime();

        DateTime dt(date, time);

        showDateTimeMenu(dt);

    } catch(const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        clearInputBuffer();
        return 1;
    }
    return 0;
}
