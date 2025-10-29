#include <iostream>
#include <limits>
#include <stdexcept>
#include "datetime.h"

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

Date inputDate() {
    int d, m, y;
    while (true) {
        cout << "Введите дату (день месяц год через пробел): ";
        cin >> d >> m >> y;

        if (cin.fail()) {
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
        cin >> h >> min >> s;

        if (cin.fail()) {
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

void showDateTimeMenu(DateTime& dt) {
    int choice;
    while (true) {
        cout << "\nТекущие значения: " << dt.printDateTime() << endl;
        cout << "Главное меню:\n"
             << "1. Работа с датой\n"
             << "2. Работа со временем\n"
             << "0. Выход\n"
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
                                    dt.increaseHour(value); // Используем методы DateTime
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
                case 0:
                    cout << "\nФинальные значения: " << dt.printDateTime() << endl;
                    return;
                default:
                    cerr << "Неверный выбор! Попробуйте снова.\n";
            }
        } catch (const char* e) {
            cerr << "Ошибка: " << e << endl;
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

    } catch (const char* e) {
        cerr << "Критическая ошибка: " << e << endl;
        return 1;
    }
    return 0;
}
