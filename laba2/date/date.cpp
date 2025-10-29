#include "date.h"
#include <string>
#include <sstream>
#include <cstring>

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
// Конструктор из строки "DD.MM.YY"
Date::Date(const std::string &dateStr) {
  char dot;
  int d, m, y;
  std::stringstream iss(dateStr);

  if (!(iss >> d >> dot >> m >> dot >> y) || dot != '.') {
    throw ("Неверный формат даты!");
  }

  if (!isValidDate(d, m, y)) {
    throw ("Некорректная дата!");
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

std::string Date::printDate() const {
    return std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
}


//Перегрузка ОПЕРТОРОВ + И -
Date Date::operator+(int days) const {
    Date result(*this);
    result.increaseDay(days);
    return result;
}

Date Date::operator-(int days) const {
    Date result(*this);
    result.decreaseDay(days);
    return result;
}

Date& Date::operator+=(int days) {
    increaseDay(days);
    return *this;
}

Date& Date::operator-=(int days) {
    decreaseDay(days);
    return *this;
}

//оператор присваивания
Date& Date::operator=(const Date& other) {

    if(&other != this)
    {
            day = other.day;
            month = other.month;
            year = other.year;
    }
    return *this;
}


Date Date::operator+(const Date& other) const {

  //Сделать проверку
  return Date(
            day + other.day,
            month + other.month,
            year + other.year
        );

}

Date Date::operator-(const Date& other) const {

  //Сделать проверку
  return Date(
            day - other.day,
            month - other.month,
            year - other.year
        );

}

Date& Date::operator+=(const Date& other) {

  day += other.day;
  month += other.month;
  year += other.year;
  return *this;

}
Date& Date::operator-=(const Date& other) {

  day -= other.day;
  month -= other.month;
  year -= other.year;
  return *this;

}

Date::operator char*() const {

  std::string dt = printDate();
  char* result = new char[dt.length() + 1];
  strcpy(result, dt.c_str());
  return result;

}
