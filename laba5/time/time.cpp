#include "time.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>


//Проверка времени
bool Time::isValidTime(int hour, int minute, int second) const {
    return (hour >= 0 && hour < 24) &&
           (minute >= 0 && minute < 60) &&
           (second >= 0 && second < 60);
}

//Конструкторы

//Конструктор по умолчанию
Time::Time() : hour(0), minute(0), second(0) {}

//Конструктор параметризированный
Time::Time(int h, int m, int s) {
  if (!isValidTime(h, m, s)) {
          throw "Некорректное время!";
      }
      hour = h;
      minute = m;
      second = s;
}

//Конструктор копирования
Time::Time(const Time &other) : hour(other.hour), minute(other.minute), second(other.second) {}

// Конструктор из строки "HH.MM.SS"
Time::Time(const std::string &timeStr) {

  char dot;
  int h, m, s;
  std::stringstream iss(timeStr);

  if (!(iss >> h >> dot >> m >> dot >> s) || dot != ':') {
    throw ("Неверный формат времени!");
  }

  if (!isValidTime(h, m, s)) {
    throw ("Некорректное время!");
  }

  hour = h;
  minute = m;
  second = s;
}

//Геттеры Time
int Time::getHour() const { return hour; }
int Time::getMinute() const { return minute; }
int Time::getSecond() const { return second; }

// Сеттеры Time
void Time::setHour(int hour) {
    if (!isValidTime(hour, this->minute, this->second)) {
        throw "Некорректный час!";
    }
    this->hour = hour;
}

void Time::setMinute(int minute) {
    if (!isValidTime(this->hour, minute, this->second)) {
        throw "Некорректная минута!";
    }
    this->minute = minute;
}

void Time::setSecond(int second) {
    if (!isValidTime(this->hour, this->minute, second)) {
        throw"Некорректная секунда!";
    }
    this->second = second;
}
// Увеличение часов
int Time::increaseHour(int i) {
    if (i < 0) {
        throw "Некорректное значение!";
    }
    hour += i;
    int daysPassed = hour / 24;
    hour %= 24;
    return daysPassed;
}

// Увеличение минут
int Time::increaseMinute(int i) {
    if (i < 0) {
        throw "Некорректное значение!";
    }
    minute += i;
    int hoursPassed = minute / 60;
    minute %= 60;
    return increaseHour(hoursPassed);
}

// Увеличение секунд
int Time::increaseSecond(int i) {
    if (i < 0) {
        throw "Некорректное значение!";
    }
    second += i;
    int minutesPassed = second / 60;
    second %= 60;
    return increaseMinute(minutesPassed);
}

// Уменьшение часов
int Time::decreaseHour(int i) {
    if (i < 0) {
        throw "Некорректное значение!";
    }
    hour -= i;
    int daysPassed = 0;
    if (hour < 0) {
        daysPassed = (-hour + 23) / 24;
        hour = 24 + (hour % 24);
    }
    return daysPassed;
}

// Уменьшение минут
int Time::decreaseMinute(int i) {
    if (i < 0) {
        throw "Некорректное значение!";
    }
    minute -= i;
    int hoursPassed = 0;
    if (minute < 0) {
        hoursPassed = (-minute + 59) / 60;
        minute = 60 + (minute % 60);
    }
    return decreaseHour(hoursPassed);
}

// Уменьшение секунд
int Time::decreaseSecond(int i) {
    if (i < 0) {
        throw "Некорректное значение!";
    }
    second -= i;
    int minutesPassed = 0;
    if (second < 0) {
        minutesPassed = (-second + 59) / 60;
        second = 60 + (second % 60);
    }
    return decreaseMinute(minutesPassed);
}
/*
// Увеличение часов
void Time::increaseHour(int i) {
    bool flag = false;
    if (i < 0) {
      throw "Некорректное значение!";
    }
    hour += i;
    int days = 0;
    if (hour >= 24) {
        flag = true;
        days = hour/24;
        //std:: cout << days << std:: endl;
        hour %= 24; // Сбрасываем часы, если они превышают 23

    }


    //if (flag == true) {

      //return days;
    //}
}

// Увеличение минут
void Time::increaseMinute(int i) {
    if (i < 0) {
      throw "Некорректное значение!";
    }
    minute += i;
    if (minute >= 60) {
        increaseHour(minute / 60); // Увеличиваем часы на количество переполнений
        minute %= 60; // Сбрасываем минуты
    }
}

// Увеличение секунд
void Time::increaseSecond(int i) {
    if (i < 0) {
      throw "Некорректное значение!";
    }
    second += i;
    if (second >= 60) {
        increaseMinute(second / 60); // Увеличиваем минуты на количество переполнений
        second %= 60; // Сбрасываем секунды
    }
}

// Уменьшение часов
void Time::decreaseHour(int i) {
    //bool flag = true;
    if (i < 0) {
      throw "Некорректное значение!";
    }
    hour -= i;
    int days = 0;
    if (hour < 0) {
        //flag = false;
        days = ((-hour + 23) / 24);
        std:: cout << days << std::endl;
        hour = 24 + (hour % 24); // Корректируем часы, если они меньше 0
    }

    //if (flag == false) {

      //decreaseDay(days);

    //}
}

// Уменьшение минут
void Time::decreaseMinute(int i) {
    if (i < 0) {
      throw "Некорректное значение!";
    }
    minute -= i;
    if (minute < 0) {
        decreaseHour((-minute) / 60 + 1); // Уменьшаем часы на количество переполнений
        minute = 60 + (minute % 60); // Корректируем минуты
    }
}

// Уменьшение секунд
void Time::decreaseSecond(int i) {
    if (i < 0) {
      throw "Некорректное значение!";
    }
    second -= i;
    if (second < 0) {
        decreaseMinute((-second) / 60 + 1); // Уменьшаем минуты на количество переполнений
        second = 60 + (second % 60); // Корректируем секунды
    }
}
*/
// Вывод данных
std::string Time::printTime()const {
      return std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second);
}

//Перегрузка оператора присваивания
Time& Time::operator=(const Time& other) {
      if (this != &other) {
          hour = other.hour;
          minute = other.minute;
          second = other.second;
      }
      return *this;
}

// Перегрузка Операторов + и -
Time Time::operator+(int hour) const {
  Time result(*this);
  result.increaseHour(hour);
  return result;
}

Time Time::operator-(int hour) const {
  Time result(*this);
  result.decreaseHour(hour);
  return result;
}

Time& Time::operator+=(int hour) {
  increaseHour(hour);
  return *this;
}

Time& Time::operator-=(int hour) {
  decreaseHour(hour);
  return *this;
}


Time Time::operator+(const Time& other) const {
    int newHour = hour + other.hour;
    int newMinute = minute + other.minute;
    int newSecond = second + other.second;

    // Нормализация секунд и минут
    newMinute += newSecond / 60;
    newSecond %= 60;
    if (newSecond < 0) {
        newSecond += 60;
        newMinute--;
    }

    newHour += newMinute / 60;
    newMinute %= 60;
    if (newMinute < 0) {
        newMinute += 60;
        newHour--;
    }

    // Нормализация часов
    newHour %= 24;
    if (newHour < 0) {
        newHour += 24;
    }

    return Time(newHour, newMinute, newSecond);
}

Time Time::operator-(const Time& other) const {
    int newHour = hour - other.hour;
    int newMinute = minute - other.minute;
    int newSecond = second - other.second;

    // Нормализация секунд и минут
    if (newSecond < 0) {
        newSecond += 60;
        newMinute--;
    }

    if (newMinute < 0) {
        newMinute += 60;
        newHour--;
    }

    // Нормализация часов
    if (newHour < 0) {
        newHour += 24;
    }

    return Time(newHour, newMinute, newSecond);
}

Time& Time::operator+=(const Time& other) {
    second += other.second;
    minute += other.minute;
    hour += other.hour;

    // Нормализация
    minute += second / 60;
    second %= 60;
    if (second < 0) {
        second += 60;
        minute--;
    }

    hour += minute / 60;
    minute %= 60;
    if (minute < 0) {
        minute += 60;
        hour--;
    }

    hour %= 24;
    if (hour < 0) {
        hour += 24;
    }

    return *this;
}

Time& Time::operator-=(const Time& other) {
    second -= other.second;
    minute -= other.minute;
    hour -= other.hour;

    // Нормализация
    if (second < 0) {
        second += 60;
        minute--;
    }

    if (minute < 0) {
        minute += 60;
        hour--;
    }

    if (hour < 0) {
        hour += 24;
    }

    return *this;
}


/*
Time Time::operator+(const Time& other) const {

  //Сделать проверку
  return Time(
            hour + other.hour,
            minute + other.minute,
            second + other.second
        );

}

Time Time::operator-(const Time& other) const {

  //Сделать проверку
  return Time(
            hour - other.hour,
            minute - other.minute,
            second - other.second
        );

}

Time& Time::operator+=(const Time& other) {

  hour += other.hour;
  minute += other.minute;
  second += other.second;
  return *this;

}
Time& Time::operator-=(const Time& other) {

  hour -= other.hour;
  minute -= other.minute;
  second -= other.second;
  return *this;

}
*/
Time::operator char*() const {

  std::string dt = printTime();
  char* result = new char[dt.length() + 1];
  strcpy(result, dt.c_str());
  return result;

}


std::ostream& operator << (std::ostream &os, const Time &time) {

  return os << time.getHour() << ":" << time.getMinute() << ":" << time.getSecond();

}

std::istream& operator >> (std::istream& in, Time& time) {

  int hour;
  int minute;
  int second;

  char sep;

  // Пробуем прочитать первый элемент
  if (!(in >> hour)) {
      in.setstate(std::ios::failbit);
      return in;
  }

  // Смотрим следующий символ
  sep = in.peek();

  if (sep == ':') {
      in >> sep >> minute >> sep >> second;
      if (sep != ':') {
          in.setstate(std::ios::failbit);
          return in;
      }
  } else {

      in >> minute >> second;
  }

  if (!time.isValidTime(hour, minute, second)) {
      throw ("Некорректное время!");
  }

  time.setHour(hour);
  time.setMinute(minute);
  time.setSecond(second);

  return in;


}
