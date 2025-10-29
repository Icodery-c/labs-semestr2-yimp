#include "datetime.h"
#include <iostream>
#include <iomanip>
#include <clocale>
#include <chrono>

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

    // Проверка форматов:
    // 1) UTC±hh
    // 2) UTC±hh:mm
    // 3) UTC±h
    if (tz[3] == '+' || tz[3] == '-') {
        size_t colon_pos = tz.find(':');

        if (colon_pos != string::npos) {
            // Формат с минутами UTC±hh:mm
            if (tz.size() != 9) return false;

            string hours = tz.substr(4, 2);
            string minutes = tz.substr(7, 2);

            if (!isdigit(hours[0]) || !isdigit(hours[1]) || !isdigit(minutes[0]) || !isdigit(minutes[1]))
                return false;

            int h = stoi(hours);
            int m = stoi(minutes);
            return (h >= 0 && h <= 23 && m >= 0 && m <= 59);
        } else {
            // Формат без минут UTC±h или UTC±hh
            string hour_part = tz.substr(4);
            if (hour_part.empty()) return false;

            for (char c : hour_part) {
                if (!isdigit(c)) return false;
            }

            int h = stoi(hour_part);
            return (h >= 0 && h <= 23);
        }
    }

    return false;
}


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
             //<< "6. Переключить автообновление (" << (timer.isAutoUpdateEnabled() ? "ВКЛ" : "ВЫКЛ") << ")\n"
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

                //case 6:
                    //timer.setAutoUpdate(!timer.isAutoUpdateEnabled());
                    //cout << "Автообновление " << (timer.isAutoUpdateEnabled() ? "включено" : "выключено") << endl;
                    //break;

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
      cout << "Введите часовой пояс (например Europe/Moscow, UTC+3, UTC-05:00, America/New_York): ";
      cin >> tz;

      if (isTimeZoneValid(tz)) {
          dtz.setTimeZone(tz);
          cout << "Часовой пояс установлен на: " << dtz.getTimeZone() << endl;
          valid = true;
      } else if (isValidUTCOffset(tz)) {
          // Обработка UTC смещения
          dtz.setTimeZone(tz); // Предполагая, что ваш класс поддерживает это
          cout << "Часовой пояс установлен на: " << tz << endl;
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

                    cout << "Системное время: " << std::chrono::system_clock::to_time_t(now) << endl;
                    cout << "Локальное время: " << std::format("{:%d.%m.%Y %H:%M:%S}", local_time) << endl;
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

int main() {
    // Устанавливаем локаль для поддержки русского языка
    setlocale(LC_ALL, "Russian");

    int choice;

    while(true) {
        cout << "\n=== Главное меню ===\n"
             << "1. Тестирование таймера\n"
             << "2. Тестирование часовых поясов\n"
             << "0. Выход\n"
             << "Выбор: ";
        cin >> choice;

        switch(choice) {
            case 1:
                testTimer();
                break;

            case 2:
                testTimeZone();
                break;

            case 0:
                return 0;

            default:
                cout << "Неверный выбор!\n";
        }
    }
}
