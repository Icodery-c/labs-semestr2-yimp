#include "datetime.h"
#include <string>
 #include <iostream>

//Проверка даты
bool Date::isValidDate(int day, int month, int year) {

  if (month < 1 || month > 12)
    return false;

  if (year < 1)
    return false;

  if (day < 1 || day > 31)
    return false;

  if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    return false;

  if (month == 2) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        if (day > 29)
          return false;
         } else {
           if (day > 28)
             return false;
         }
       }

       return true;
}

// Вспомогательная функция для определения количества дней в месяце
int daysInMonth(int month, int year) {
    if (month == 2) {
        // Проверка на високосный год
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return 29;
        } else {
            return 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}

//Конструкторы

//Конструктор по умолчанию
Date::Date() : day(1), month(1), year(1) {}

//Конструктор параметризированный
Date::Date(int d, int m, int y) {
  if (!isValidDate(d, m, y)) {
          throw "Некорректная дата!";
      }
      day = d;
      month = m;
      year = y;
}

//Конструктор копирования
Date::Date(const Date &other) : day(other.day), month(other.month), year(other.year) {}


//Геттеры Date

int Date::getDay() { return day; }
int Date::getMonth() { return month; }
int Date::getYear() { return year; }

//Сеттеры
void Date::setDay(int day) {

  if(!isValidDate(day,this->month,this->year)) {
    throw "Некоректный день!";
  }
  this->day = day;
}


void Date::setMonth(int month) {
  if(!isValidDate(this->day,month,this->year)) {
    throw "Некоректный месяц!";
  }
  this->month = month;

}
void Date::setYear(int year) {
  if(!isValidDate(this->day,this->month,year)) {
    throw "Некоректный год!";
  }
  this->year = year;

}

// Увеличение дней
void Date::increaseDay(int i) {
    if (i < 0) {
      throw "Некоректное значение!";
    }
    day += i;
    while (day > daysInMonth(month, year)) {
        day -= daysInMonth(month, year);
        increaseMonth(1);
    }
}

// Увеличение месяцев
void Date::increaseMonth(int i) {
    if (i < 0) {
      throw "Некоректное значение!";
    }
    month += i;
    while (month > 12) {
        month -= 12;
        increaseYear(1);
    }
}

// Увеличение лет
void Date::increaseYear(int i) {
    if (i < 0) {
      throw "Некоректное значение!";
    }
    year += i;
}

// Уменьшение дней
void Date::decreaseDay(int i) {
    if (i < 0) {
      throw "Некоректное значение!";
    }
    day -= i;
    while (day < 1) {
        decreaseMonth(1);
        day += daysInMonth(month, year);
    }
}

// Уменьшение месяцев
void Date::decreaseMonth(int i) {
    if (i < 0) {
      throw "Некоректное значение!";
    }
    month -= i;
    while (month < 1) {
        month += 12;
        decreaseYear(1);
    }
}

// Уменьшение лет
void Date::decreaseYear(int i) {
    if (i < 0) {
      throw "Некоректное значение!";
    }
    year -= i;
}


std::string Date::printDate() {
    return std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
}

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
std::string Time::printTime() {
      return std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second);
}



std::string DateTime::printDateTime() {
    return date.printDate() + " " + time.printTime();
}

// Конструкторы
//DateTime::DateTime() : date(), time() {}  // По умолчанию: 1.1.1 00:00:00

//DateTime::DateTime(int day, int month, int year, int hour, int minute, int second)
    //: date(day, month, year), time(hour, minute, second) {}

//DateTime::DateTime(const DateTime &other) : date(other.date), time(other.time) {}

DateTime::DateTime(const Date& d, const Time& t) : date(d), time(t) {}

// Увеличение времени с обновлением даты
void DateTime::increaseHour(int hours) {
    int daysPassed = time.increaseHour(hours);
    if (daysPassed > 0) {
        date.increaseDay(daysPassed);
    }
}

void DateTime::increaseMinute(int minutes) {
    int daysPassed = time.increaseMinute(minutes);
    if (daysPassed > 0) {
        date.increaseDay(daysPassed);
    }
}

void DateTime::increaseSecond(int seconds) {
    int daysPassed = time.increaseSecond(seconds);
    if (daysPassed > 0) {
        date.increaseDay(daysPassed);
    }
}

// Уменьшение времени с обновлением даты
void DateTime::decreaseHour(int hours) {
    int daysPassed = time.decreaseHour(hours);
    if (daysPassed > 0) {
        date.decreaseDay(daysPassed);
    }
}

void DateTime::decreaseMinute(int minutes) {
    int daysPassed = time.decreaseMinute(minutes);
    if (daysPassed > 0) {
        date.decreaseDay(daysPassed);
    }
}

void DateTime::decreaseSecond(int seconds) {
    int daysPassed = time.decreaseSecond(seconds);
    if (daysPassed > 0) {
        date.decreaseDay(daysPassed);
    }
}

Date& DateTime::getDate() {
    return date;
}

Time& DateTime::getTime() {
    return time;
}

const Date& DateTime::getDate() const {
    return date;
}

const Time& DateTime::getTime() const {
    return time;
}
