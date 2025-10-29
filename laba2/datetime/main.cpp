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

void testDateOperators() {
    cout << "\n=== Тестирование операторов Date ===\n";
    Date d1 = inputDate();
    Date d2 = inputDate();

    int choice;
    while (true) {
        cout << "\nВыберите оператор для тестирования:\n"
             << "1. d1 + int (добавить дни)\n"
             << "2. d1 - int (вычесть дни)\n"
             << "3. d1 + d2 (сложить даты)\n"
             << "4. d1 - d2 (вычесть даты)\n"
             << "5. d1 += int\n"
             << "6. d1 -= int\n"
             << "7. Преобразование d1 and d2 в char*\n"
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
                case 0:
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

void testTimeOperators() {
    cout << "\n=== Тестирование операторов Time ===\n";
    Time t1 = inputTime();
    Time t2 = inputTime();

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
                case 0:
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

void testDateTimeOperators() {
    cout << "\n=== Тестирование операторов DateTime ===\n";
    cout << "Введите первую дату и время:\n";
    DateTime dt1(inputDate(), inputTime());

    cout << "\nВведите вторую дату и время:\n";
    DateTime dt2(inputDate(), inputTime());

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
                case 0:
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

void showDateTimeMenu(DateTime& dt) {
    int choice;
    while (true) {
        cout << "\nТекущие значения: " << dt.printDateTime() << endl;
        cout << "Главное меню:\n"
             << "1. Работа с датой\n"
             << "2. Работа со временем\n"
             << "3. Тест операторов Date\n"
             << "4. Тест операторов Time\n"
             << "5. Тест операторов DateTime\n"
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
