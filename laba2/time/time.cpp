#include "time.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
//Проверка времени
bool Time::isValidTime(int hour, int minute, int second) {
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


//Конструктор копирования
Time::Time(const Time &other) : hour(other.hour), minute(other.minute), second(other.second) {}

//Геттеры Time
int Time::getHour() { return hour; }
int Time::getMinute() { return minute; }
int Time::getSecond() { return second; }

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
void Time::increaseHour(int i) {
    //bool flag = false;
    if (i < 0) {
      throw "Некорректное значение!";
    }
    hour += i;
    int days = 0;
    if (hour >= 24) {
        //flag = true;
        days = hour/24;
        //std:: cout << days << std:: endl;
        hour %= 24; // Сбрасываем часы, если они превышают 23

    }

    //if (flag == true) {

      //std:: cout << "Check!" << days << std::endl;
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
        //std:: cout << days << std::endl;
        hour = 24 + (hour % 24); // Корректируем часы, если они меньше 0
    }

    //if (flag == false) {
      //std:: cout << "Check!" << std::endl;

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

// Вывод данных
std::string Time::printTime() const {
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

Time::operator char*() const {

  std::string dt = printTime();
  char* result = new char[dt.length() + 1];
  strcpy(result, dt.c_str());
  return result;

}
