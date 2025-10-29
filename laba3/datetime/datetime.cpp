#include "datetime.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>

//Проверка даты
bool Date::isValidDate(int day, int month, int year) const {

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

bool Date::isLeapYear(int year) const {
    if (year % 4 != 0) {
        return false;    // Обычный год
    } else if (year % 100 != 0) {
        return true;     // Високосный год
    } else if (year % 400 != 0) {
        return false;    // Обычный год
    } else {
        return true;     // Високосный год
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


//Геттеры Date

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

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
/*void Date::decreaseYear(int i) {
    if (i < 0) {
      throw "Некоректное значение!";
    }
    year -= i;
}
*/
void Date::decreaseYear(int i) {
    if (i < 0) {
        throw "Некоректное значение!";
    }
    year -= i;
    // Добавляем проверку на валидность года после уменьшения
    if (year < 1) {
        year += i; // Откатываем изменение
        throw "Год не может быть меньше 1!";
    }
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
/*
Date Date::operator+(const Date& other) const {
    int newDay = day + other.day;
    int newMonth = month + other.month;
    int newYear = year + other.year;

    // Нормализация даты
    while (newDay > daysInMonth(newMonth, newYear)) {
        newDay -= daysInMonth(newMonth, newYear);
        newMonth++;
        if (newMonth > 12) {
            newMonth = 1;
            newYear++;
        }
    }

    while (newMonth > 12) {
        newMonth -= 12;
        newYear++;
    }

    if (!isValidDate(newDay, newMonth, newYear)) {
        throw ("Результат сложения дат недопустим");
    }

    return Date(newDay, newMonth, newYear);
}
Date Date::operator-(const Date& other) const {
    int newDay = day - other.day;
    int newMonth = month - other.month;
    int newYear = year - other.year;

    // Нормализация даты
    while (newDay < 1) {
        newMonth--;
        if (newMonth < 1) {
            newMonth = 12;
            newYear--;
        }
        newDay += daysInMonth(newMonth, newYear);
    }

    while (newMonth < 1) {
        newMonth += 12;
        newYear--;
    }

    if (newYear < 1) {
        throw ("Результат вычитания дат недопустим (год < 1)");
    }

    if (!isValidDate(newDay, newMonth, newYear)) {
        throw std::invalid_argument("Результат вычитания дат недопустим");
    }

    return Date(newDay, newMonth, newYear);
}

Date& Date::operator+=(const Date& other) {
    day += other.day;
    month += other.month;
    year += other.year;

    // Нормализация дней
    while (day > daysInMonth(month, year)) {
        day -= daysInMonth(month, year);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }

    // Нормализация месяцев
    while (month > 12) {
        month -= 12;
        year++;
    }

    // Проверка валидности
    if (!isValidDate(day, month, year)) {
        throw ("Некорректная дата после сложения");
    }

    return *this;
}

Date& Date::operator-=(const Date& other) {
    day -= other.day;
    month -= other.month;
    year -= other.year;

    // Нормализация дней
    while (day < 1) {
        month--;
        if (month < 1) {
            month = 12;
            year--;
            if (year < 1) {
                throw ("Год не может быть меньше 1");
            }
        }
        day += daysInMonth(month, year);
    }

    // Нормализация месяцев
    while (month < 1) {
        month += 12;
        year--;
        if (year < 1) {
            throw ("Год не может быть меньше 1");
        }
    }

    // Проверка валидности
    if (!isValidDate(day, month, year)) {
        throw ("Некорректная дата после вычитания");
    }

    return *this;
}

*/
int Date::toDays() const {
  int total = day;
  // Добавляем дни предыдущих месяцев текущего года
  for (int m = 1; m < month; m++) {
    total += daysInMonth(m, year);
  }

  // Добавляем дни предыдущих лет
  total += 365 * (year - 1);
  // Учитываем високосные годы
  total += (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
  return total;
}

// Создание даты из количества дней
void Date::fromDays(int totalDays) {
  if (totalDays < 1) {
    throw std::invalid_argument("Invalid total days");
  }

  int y = 1;
  int m = 1;
  int d = 1;

  // Вычисляем год
  while (true) {
    int daysInYear = isLeapYear(y) ? 366 : 365;
    if (totalDays > daysInYear) {
      totalDays -= daysInYear;
      y++;
    } else {
      break;
    }
  }

  // Вычисляем месяц
  while (true) {
    int daysInM = daysInMonth(m, y);
    if (totalDays > daysInM) {
      totalDays -= daysInM;
      m++;
    } else {
      break;
    }
  }

  // Оставшиеся дни - день месяца
  d = totalDays;

  // Устанавливаем новые значения
  day = d;
  month = m;
  year = y;
}

Date Date::operator+(const Date& other) const {
  Date result;
  result.fromDays(this->toDays() + other.toDays());
  return result;
}

Date Date::operator-(const Date& other) const {
  int diff = this->toDays() - other.toDays();
  if (diff < 1) {
    throw ("Результат вычитания дат недопустим (дата до 1 года)");
  }
  Date result;
  result.fromDays(diff);
  return result;
}

Date& Date::operator+=(const Date& other) {
  fromDays(this->toDays() + other.toDays());
  return *this;
}

Date& Date::operator-=(const Date& other) {
  int diff = this->toDays() - other.toDays();
  if (diff < 1) {
    throw ("Результат вычитания дат недопустим (дата до 1 года)");
  }
  fromDays(diff);
  return *this;
}




/*
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
            day + other.day,
            month + other.month,
            year + other.year
        );

}

Date& Date::operator+=(const Date& other) {

  day += other.day;
  month += other.month;
  year += other.year;
  return *this;

}
Date& Date::operator-=(const Date& other) {

  day += other.day;
  month += other.month;
  year += other.year;
  return *this;

}
*/

Date::operator char*() const {

  std::string dt = printDate();
  char* result = new char[dt.length() + 1];
  strcpy(result, dt.c_str());
  return result;

}

std::ostream& operator << (std::ostream &os, const Date &date) {

  return os << date.getDay() << "." << date.getMonth() << "." << date.getYear();

}



/*
std::istream& operator >> (std::istream& in, Date& date) {

  int day;
  int month;
  int year;


    if (!(in >> day >> month >> year)) {
        in.setstate(std::ios::failbit);
        return in;
    }

    // Проверяем корректность даты
    if (!date.isValidDate(day, month, year)) {
        in.setstate(std::ios::failbit);
        throw "Некорректная дата!";
    }



  date.setDay(day);
  date.setMonth(month);
  date.setYear(year);
  return in;


}
*/

std::istream& operator>>(std::istream& in, Date& date) {
    int day, month, year;
    char sep;

    // Пробуем прочитать первый элемент
    if (!(in >> day)) {
        in.setstate(std::ios::failbit);
        return in;
    }

    // Смотрим следующий символ
    sep = in.peek();

    if (sep == '.') {
        // Формат DD.MM.YYYY
        in >> sep >> month >> sep >> year;
        if (sep != '.') {
            in.setstate(std::ios::failbit);
            return in;
        }
    } else {
        // Формат DD MM YYYY
        in >> month >> year;
    }

    if (!date.isValidDate(day, month, year)) {
        throw ("Некорректная дата!");
    }


    date.setDay(day);
    date.setMonth(month);
    date.setYear(year);
    return in;
}


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
/*int Time::decreaseHour(int i) {
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
}*/
int Time::decreaseHour(int i) {
    if (i < 0) {
        throw "Некорректное значение!";
    }


    int totalHours = hour - i;


    while (totalHours < 0) {
        totalHours += 24;
    }

    hour = totalHours % 24;


    return (totalHours < 0) ? 1 : 0;
}

// Уменьшение минут
/*
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
*/

int Time::decreaseMinute(int i) {
    if (i < 0) {
        throw "Некорректное значение!";
    }

    int totalMinutes = hour * 60 + minute;
    totalMinutes -= i;


    while (totalMinutes < 0) {
        totalMinutes += 24 * 60;
    }


    hour = (totalMinutes / 60) % 24;
    minute = totalMinutes % 60;


    return (totalMinutes < 0) ? 1 : 0;
}
// Уменьшение секунд
int Time::decreaseSecond(int i) {
    if (i < 0) {
        throw "Некорректное значение!";
    }
    int totalSeconds = hour * 3600 + minute * 60 + second;
    totalSeconds -= i;


    while (totalSeconds < 0) {
        totalSeconds += 24 * 3600;
    }
    hour = (totalSeconds / 3600) % 24;
    minute = (totalSeconds / 60) % 60;
    second = totalSeconds % 60;

    return (totalSeconds < 0) ? 1 : 0;
}
/*int Time::decreaseSecond(int i) {
    if (i < 0) {
        throw "Некорректное значение!";
    }

    int totalSecond = hour * 60 * 60 + minute * 60 + second;

    second -
    int minutesPassed = 0;
    if (second < 0) {
        minutesPassed = (-second + 59) / 60;
        second = 60 + (second % 60);
    }
    return decreaseMinute(minutesPassed);
}*/
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

/*
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
*/


int Time::toSeconds() const {
  return hour * 3600 + minute * 60 + second;
}

void Time::fromSeconds(int totalSeconds) {
  // Обрабатываем отрицательные значения
  if (totalSeconds < 0) {
    totalSeconds += 24 * 3600 * ((-totalSeconds) / (24 * 3600) + 1);
  }

  totalSeconds %= (24 * 3600);
  hour = totalSeconds / 3600;
  minute = (totalSeconds % 3600) / 60;
  second = totalSeconds % 60;
}


Time Time::operator+(const Time& other) const {
  Time result;
  result.fromSeconds(this->toSeconds() + other.toSeconds());
  return result;
}

Time Time::operator-(const Time& other) const {
  Time result;
  result.fromSeconds(this->toSeconds() - other.toSeconds());
  return result;
}

Time& Time::operator+=(const Time& other) {
  fromSeconds(this->toSeconds() + other.toSeconds());
  return *this;
}

Time& Time::operator-=(const Time& other) {
  fromSeconds(this->toSeconds() - other.toSeconds());
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


std::string DateTime::printDateTime() const {
    return date.printDate() + " " + time.printTime();
}

// Конструкторы
//DateTime::DateTime() : date(), time() {}  // По умолчанию: 1.1.1 00:00:00

//DateTime::DateTime(int day, int month, int year, int hour, int minute, int second)
    //: date(day, month, year), time(hour, minute, second) {}

//DateTime::DateTime(const DateTime &other) : date(other.date), time(other.time) {}

DateTime::DateTime(const Date& d, const Time& t) : date(d), time(t) {}
DateTime::DateTime() : date(Date()), time(Time()) {}  // Конструктор по умолчанию

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

/*void DateTime::decreaseMinute(int minutes) {
    int daysPassed = time.decreaseMinute(minutes);
    if (daysPassed > 0) {
        date.decreaseDay(daysPassed);
    }
}
*/
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

void DateTime::setTime(const Time& time) {
  if (!time.isValidTime(time.getHour(), time.getMinute(), time.getSecond())) {
    throw std::invalid_argument("Invalid time");
  }
  this->time = time;
}

void DateTime::setDate(const Date& date) {
  if (!date.isValidDate(date.getDay(), date.getMonth(), date.getYear())) {
    throw std::invalid_argument("Invalid date");
  }
  this->date = date;
}



//Перегрузка оператора присваивания
DateTime& DateTime::operator=(const DateTime& other) {
    if (&other != this) {
        date = other.date;
        time = other.time;
    }
    return *this;
}

DateTime::operator char*() const {

    std::string dtStr = printDateTime();
    char* result = new char[dtStr.length() + 1];
    strcpy(result, dtStr.c_str());
    return result;
}

DateTime DateTime::operator+(int days)  {
    DateTime result(*this);
    result.date.increaseDay(days);
    return result;
}

DateTime DateTime::operator-(int days)  {
    DateTime result(*this);
    result.date.decreaseDay(days);
    return result;
}

DateTime& DateTime::operator+=(int days) {
    date.increaseDay(days);
    return *this;
}

DateTime& DateTime::operator-=(int days) {
    date.decreaseDay(days);
    return *this;
}

// Оператор сложения
/*DateTime DateTime::operator+(const DateTime& other) const {
    DateTime result = *this; // Создаем копию текущего объекта

    // Работаем с временем через промежуточные переменные
    int newSecond = result.time.getSecond() + other.time.getSecond();
    int newMinute = result.time.getMinute() + other.time.getMinute();
    int newHour = result.time.getHour() + other.time.getHour();

    // Обрабатываем переполнение секунд
    if (newSecond >= 60) {
        newMinute += newSecond / 60;
        newSecond %= 60;
    }

    // Обрабатываем переполнение минут
    if (newMinute >= 60) {
        newHour += newMinute / 60;
        newMinute %= 60;
    }

    // Обрабатываем переполнение часов (новый день)
    if (newHour >= 24) {
        result.date.increaseDay(newHour / 24);
        newHour %= 24;
    }

    // Устанавливаем новое время
    result.time.setHour(newHour);
    result.time.setMinute(newMinute);
    result.time.setSecond(newSecond);

    // Добавляем дату через промежуточные переменные
    int otherDay = other.date.getDay();
    int otherMonth = other.date.getMonth();
    int otherYear = other.date.getYear();

    result.date.increaseDay(otherDay);
    result.date.increaseMonth(otherMonth);
    result.date.increaseYear(otherYear);

    // Проверяем валидность полученной даты
    if (!result.date.isValidDate(result.date.getDay(), result.date.getMonth(), result.date.getYear())) {
        throw ("Результат сложения дат недопустим");
    }

    return result;
}
*/
DateTime DateTime::operator+(const DateTime& other) const {
  DateTime result;

  // Работаем с временем
  int thisSeconds = time.toSeconds();
  int otherSeconds = other.time.toSeconds();
  int totalSeconds = thisSeconds + otherSeconds;

  // Перенос дней из времени
  int carryDays = totalSeconds / (24 * 3600);
  result.time.fromSeconds(totalSeconds % (24 * 3600));

  // Работаем с датой
  int thisDays = date.toDays();
  int otherDays = other.date.toDays();
  result.date.fromDays(thisDays + otherDays + carryDays);

  return result;
}

DateTime DateTime::operator-(const DateTime& other) const {
  // Проверка, что текущая дата не меньше вычитаемой
  if (date.toDays() < other.date.toDays() ||
  (date.toDays() == other.date.toDays() && time.toSeconds() < other.time.toSeconds())) {
    throw ("Вычитаемая дата/время больше исходной");
  }

  DateTime result;

  // Работаем с временем
  int thisSeconds = time.toSeconds();
  int otherSeconds = other.time.toSeconds();
  int totalSeconds = thisSeconds - otherSeconds;

  // Обработка отрицательного времени
  int borrowDays = 0;
  if (totalSeconds < 0) {
    borrowDays = 1;
    totalSeconds += 24 * 3600;
  }
  result.time.fromSeconds(totalSeconds);

  // Работаем с датой
  int thisDays = date.toDays();
  int otherDays = other.date.toDays();
  int totalDays = thisDays - otherDays - borrowDays;

  if (totalDays < 1) {
    throw "Результат вычитания дат недопустим (год < 1)";
  }
  result.date.fromDays(totalDays);

  return result;
}

DateTime& DateTime::operator+=(const DateTime& other) {
  *this = *this + other;
  return *this;
}

DateTime& DateTime::operator-=(const DateTime& other) {
  *this = *this - other;
  return *this;
}

/*
// Оператор вычитания
DateTime DateTime::operator-(const DateTime& other) const {
    // Получаем значения через промежуточные переменные
    int thisDay = date.getDay();
    int thisMonth = date.getMonth();
    int thisYear = date.getYear();
    int otherDay = other.date.getDay();
    int otherMonth = other.date.getMonth();
    int otherYear = other.date.getYear();

    // Проверяем, что текущая дата не меньше вычитаемой
    if (thisYear < otherYear ||
        (thisYear == otherYear && thisMonth < otherMonth) ||
        (thisYear == otherYear && thisMonth == otherMonth && thisDay < otherDay)) {
        throw ("Вычитаемая дата больше исходной");
    }

    DateTime result = *this;

    // Вычитаем время через промежуточные переменные
    int seconds = result.time.getSecond() - other.time.getSecond();
    int minutes = result.time.getMinute();
    int hours = result.time.getHour();

    if (seconds < 0) {
        seconds += 60;
        minutes--;
    }

    minutes -= other.time.getMinute();
    if (minutes < 0) {
        minutes += 60;
        hours--;
    }

    hours -= other.time.getHour();
    if (hours < 0) {
        hours += 24;
        result.date.decreaseDay(1);
    }

    result.time.setSecond(seconds);
    result.time.setMinute(minutes);
    result.time.setHour(hours);

    // Вычитаем дату
    result.date.decreaseDay(otherDay);
    result.date.decreaseMonth(otherMonth);
    result.date.decreaseYear(otherYear);

    // Проверяем валидность полученной даты
    if (!result.date.isValidDate(result.date.getDay(), result.date.getMonth(), result.date.getYear())) {
        throw ("Результат вычитания дат недопустим");
    }

    // Проверяем, что год не стал меньше 1
    if (result.date.getYear() < 1) {
        throw ("Результат вычитания дат недопустим (год < 1)");
    }

    return result;
}
*/

/*
// Оператор сложения
DateTime DateTime::operator+(const DateTime& other) const {
    DateTime result = *this; // Создаем копию текущего объекта

    // Работаем с временем через промежуточные переменные
    int newSecond = result.time.getSecond() + other.time.getSecond();
    int newMinute = result.time.getMinute() + other.time.getMinute();
    int newHour = result.time.getHour() + other.time.getHour();

    // Обрабатываем переполнение секунд
    if (newSecond >= 60) {
        newMinute += newSecond / 60;
        newSecond %= 60;
    }

    // Обрабатываем переполнение минут
    if (newMinute >= 60) {
        newHour += newMinute / 60;
        newMinute %= 60;
    }

    // Обрабатываем переполнение часов (новый день)
    if (newHour >= 24) {
        result.date.increaseDay(newHour / 24);
        newHour %= 24;
    }

    // Устанавливаем новое время
    result.time.setHour(newHour);
    result.time.setMinute(newMinute);
    result.time.setSecond(newSecond);

    // Добавляем дату через промежуточные переменные
    int otherDay = other.date.getDay();
    int otherMonth = other.date.getMonth();
    int otherYear = other.date.getYear();

    result.date.increaseDay(otherDay);
    result.date.increaseMonth(otherMonth);
    result.date.increaseYear(otherYear);

    return result;
}

// Оператор вычитания
DateTime DateTime::operator-(const DateTime& other) const {
    // Получаем значения через промежуточные переменные
    int thisDay = date.getDay();
    int thisMonth = date.getMonth();
    int thisYear = date.getYear();
    int otherDay = other.date.getDay();
    int otherMonth = other.date.getMonth();
    int otherYear = other.date.getYear();

    // Проверяем, что текущая дата не меньше вычитаемой
    if (thisYear < otherYear ||
        (thisYear == otherYear && thisMonth < otherMonth) ||
        (thisYear == otherYear && thisMonth == otherMonth && thisDay < otherDay)) {
        throw std::invalid_argument("Вычитаемая дата больше исходной");
    }

    DateTime result = *this;

    // Вычитаем время через промежуточные переменные
    int seconds = result.time.getSecond() - other.time.getSecond();
    int minutes = result.time.getMinute();
    int hours = result.time.getHour();

    if (seconds < 0) {
        seconds += 60;
        minutes--;
    }

    minutes -= other.time.getMinute();
    if (minutes < 0) {
        minutes += 60;
        hours--;
    }

    hours -= other.time.getHour();
    if (hours < 0) {
        hours += 24;
        result.date.decreaseDay(1);
    }

    result.time.setSecond(seconds);
    result.time.setMinute(minutes);
    result.time.setHour(hours);

    // Вычитаем дату
    result.date.decreaseDay(otherDay);
    result.date.decreaseMonth(otherMonth);
    result.date.decreaseYear(otherYear);

    return result;
}
*/
/*
DateTime& DateTime::operator+=(const DateTime& other) {
    *this = *this + other;
    return *this;
}

DateTime& DateTime::operator-=(const DateTime& other) {
    *this = *this - other;
    return *this;
}
*/

std::ostream& operator << (std::ostream &os, const DateTime &datetime) {

  return os << datetime.getDate() << " " << datetime.getTime();

}

/*
std::istream& operator>>(std::istream& in, DateTime& datetime) {
    Date date;
    Time time;

    // Пробуем прочитать дату
    if (!(in >> date)) {
        in.setstate(std::ios::failbit);
        return in;
    }

    // Пропускаем пробельные символы между датой и временем
    in >> std::ws;

    // Пробуем прочитать время
    if (!(in >> time)) {
        in.setstate(std::ios::failbit);
        return in;
    }

    // Если всё успешно, устанавливаем значения в datetime
    datetime.setDate(date);
    datetime.setTime(time);

    return in;
}

*/

std::istream& operator>>(std::istream& in, DateTime& datetime) {

    Date date;
    Time time;

    if (!(in >> date)) {
        in.setstate(std::ios::failbit);
        return in;
    }

    //пропуск пробела
    in >> std::ws;

    if (!(in >> time)) {
        in.setstate(std::ios::failbit);
        return in;
    }

    try {
        datetime.setDate(date);
        datetime.setTime(time);
    } catch (const std::invalid_argument& e) {
        in.setstate(std::ios::failbit);
        throw; // Перебрасываем исключение дальше
    }

    return in;
}
