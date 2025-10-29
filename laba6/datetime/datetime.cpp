#include "datetime.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include <chrono>
#include <thread>



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


Date::Date(int d, int m, int y) {
    if (!isValidDate(d, m, y)) {
        throw RangeException("Неверная дата: " + std::to_string(d) + "." + std::to_string(m) + "." + std::to_string(y));
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
    RangeException("Недопустимый день: " + std::to_string(day));
  }
  this->day = day;
}
void Date::setMonth(int month) {
  if(!isValidDate(this->day,month,this->year)) {
    throw RangeException("Недопустимый месяц: " + std::to_string(month));

  }
  this->month = month;

}
void Date::setYear(int year) {
  if(!isValidDate(this->day,this->month,year)) {
    throw RangeException("Недопустимый год: " + std::to_string(year));

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






Date::operator char*() const {

  std::string dt = printDate();
  char* result = new char[dt.length() + 1];
  strcpy(result, dt.c_str());
  return result;

}

std::ostream& operator << (std::ostream &os, const Date &date) {

  return os << date.getDay() << "." << date.getMonth() << "." << date.getYear();

}





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

Time::Time(int h, int m, int s) {
    if (!isValidTime(h, m, s)) {
        throw RangeException("Неверное время: " + std::to_string(h) + ":" + std::to_string(m) + ":" + std::to_string(s));
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
      throw RangeException("Недопустимый час: " + std::to_string(hour));
    }
    this->hour = hour;
}

void Time::setMinute(int minute) {
    if (!isValidTime(this->hour, minute, this->second)) {
      throw RangeException("Недопустимая минута: " + std::to_string(minute));
    }
    this->minute = minute;
}

void Time::setSecond(int second) {
    if (!isValidTime(this->hour, this->minute, second)) {
      throw RangeException("Недопустимая секунда: " + std::to_string(second));
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



std::ostream& operator << (std::ostream &os, const DateTime &datetime) {

  return os << datetime.getDate() << " " << datetime.getTime();

}



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

DateTime::DateTime(int hours, int minutes, int seconds, int day, int month, int year)
    : date(day, month, year), time(hours, minutes, seconds) {

    if(!date.isValidDate(day, month, year)) {
        throw "Некорректная дата!";
    }
    if(!time.isValidTime(hours, minutes, seconds)) {
        throw "Некорректное время!";
    }
}


DateTimeWithTimeZone::DateTimeWithTimeZone() : DateTime(), timeZone("Europe/Moscow") {}

DateTimeWithTimeZone::DateTimeWithTimeZone(const std::string& tz) : DateTime() {
	setTimeZone(tz);
}

DateTimeWithTimeZone::DateTimeWithTimeZone(const Date& d, const Time& t, const std::string& tz)
    : DateTime(d, t) {
	setTimeZone(tz);
}

DateTimeWithTimeZone::DateTimeWithTimeZone(int day, int month, int year, int hour, int minute, int second, const std::string& tz)
    : DateTime(Date(day, month, year), Time(hour, minute, second)) {
	setTimeZone(tz);
}

DateTimeWithTimeZone::DateTimeWithTimeZone(const DateTime& dt, const std::string& tz)
    : DateTime(dt) {
	setTimeZone(tz);
}

void DateTimeWithTimeZone::setTimeZone(const std::string& tz) {
	// Проверяем только если это НЕ пользовательский UTC офсет
	if (!(tz.rfind("UTC", 0) == 0 && tz.size() > 3)) {
		try {
			std::chrono::zoned_time check{tz, std::chrono::system_clock::now()};
		} catch (const std::exception& e) {
			throw ("Некорректный часовой пояс: " + tz);
		}
	}
	timeZone = tz;
}

std::string DateTimeWithTimeZone::getTimeZone() const {
	return timeZone;
}

std::chrono::seconds DateTimeWithTimeZone::parseUtcOffset(const std::string& tz) const {
    std::regex regex1(R"(UTC([+-])(\d{1,2})(?::?(\d{2}))?)");
    std::smatch match;

    if (std::regex_match(tz, match, regex1)) {
        int hours = std::stoi(match[2]);
        int minutes = 0;
        if (match[3].matched)
            minutes = std::stoi(match[3]);

        int totalSeconds = hours * 3600 + minutes * 60;
        if (match[1] == "-")
            totalSeconds = -totalSeconds;
        return std::chrono::seconds(totalSeconds);
    } else {
        throw ("Неправильный формат UTC. Примеры: UTC+3, UTC+0330, UTC-4:15");
    }
}


std::chrono::zoned_time<std::chrono::system_clock::duration>
DateTimeWithTimeZone::getCurrentTime() const {
	auto now = std::chrono::system_clock::now();

	if (timeZone.rfind("UTC", 0) == 0 && timeZone.size() > 3) {
		auto offset = parseUtcOffset(timeZone);
		auto adjustedTime = now + offset;
		return std::chrono::zoned_time("Etc/UTC", adjustedTime); // работает стабильно
	} else {
		return std::chrono::zoned_time(timeZone, now);
	}
}

std::chrono::zoned_time<std::chrono::system_clock::duration>
DateTimeWithTimeZone::fromSystemTime(const std::chrono::system_clock::time_point& sysTime) const {
	if (timeZone.rfind("UTC", 0) == 0 && timeZone.size() > 3) {
		auto offset = parseUtcOffset(timeZone);
		auto adjusted = sysTime + offset;
		return std::chrono::zoned_time("Etc/UTC", adjusted);
	} else {
		return std::chrono::zoned_time(timeZone, sysTime);
	}
}

// Конструкторы
Timer::Timer() : DateTime(), Running(false), autoUpdate(true) {}

Timer::Timer(const DateTime& dt) : DateTime(dt), Running(false), autoUpdate(true) {}

Timer::Timer(const Date& d, const Time& t, bool running)
    : DateTime(d, t), Running(running) {}


// Запуск
void Timer::StartTimer() {
    if (!Running) {
        if (autoUpdate) {
            UpdateDateTimeFromNow();
        }
        startTime = std::chrono::system_clock::now();
        Running = true;
    }
}

// Остановка
void Timer::StopTimer() {
    if (Running) {
        Running = false;
        if (autoUpdate) {
            UpdateDateTimeFromNow();
        }
    }
}

// Сброс
void Timer::ResetTimer() {
    Running = false;
    if (autoUpdate) {
        UpdateDateTimeFromNow();
    }
}

// Проверка
bool Timer::RunningTimer() const {
    return Running;
}

// Получение секунд
int Timer::GetSeconds() const {
    if (Running) {
        if (autoUpdate) {
            const_cast<Timer*>(this)->UpdateDateTimeFromNow();
        }
        auto current = std::chrono::system_clock::now();
        return static_cast<int>(
            std::chrono::duration_cast<std::chrono::seconds>(current - startTime).count()
        );
    }
    return 0;
}

// Милисекунды
int Timer::GetMilliseconds() const {
    if (Running) {
        auto current = std::chrono::system_clock::now();
        return static_cast<int>(
            std::chrono::duration_cast<std::chrono::milliseconds>(current - startTime).count()
        );
    }
    return 0;
}

// Ожидание
void Timer::WaitTimer(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

// Обновление DateTime текущим временем
void Timer::UpdateDateTimeFromNow() {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm* timeinfo = std::localtime(&now);

    Date newDate(timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);
    Time newTime(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    this->setDate(newDate);
    this->setTime(newTime);
}

// Управление autoUpdate
void Timer::setAutoUpdate(bool enable) {
    autoUpdate = enable;
}

bool Timer::isAutoUpdateEnabled() const {
    return autoUpdate;
}


bool DateTime::operator==(const DateTime& other) const {
        return date == other.date && time == other.time;
    }
bool DateTimeWithTimeZone::operator==(const DateTimeWithTimeZone& other) const {
           return static_cast<const DateTime&>(*this) == static_cast<const DateTime&>(other) &&
                  timeZone == other.timeZone;
       }

bool Timer::operator==(const Timer& other) const {
               return startTime == other.startTime && Running == other.Running;
           }

bool Date::operator==(const Date& other) const {
                   return day == other.day && month == other.month && year == other.year;
               }

bool Time::operator==(const Time& other) const {
                       return hour == other.hour && minute == other.minute && second == other.second;
                   }


DateTime::~DateTime() {}

void DateTime::print() const {
    std::cout << date.printDate() << " " << time.printTime();
}

void DateTimeWithTimeZone::print() const {
    DateTime::print();
    std::cout << " TimeZone: " << timeZone;
}

void Timer::print() const {
    DateTime::print();
    std::cout << " Timer: " << (Running ? "Running" : "Stopped");
}

// Реализация Node
template <typename T>
Node<T>::Node(T* data) : data(data), next(nullptr) {}

template <typename T>
Node<T>::~Node() {
    delete data;
}

// Реализация Stack
template <typename T>
Stack<T>::Stack() : top(nullptr), size(0) {}

template <typename T>
Stack<T>::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

template <typename T>
void Stack<T>::push(T* data) {
    if (!data) throw ("Null pointer provided to push.");
    Node<T>* newNode = new Node<T>(data);
    newNode->next = top;
    top = newNode;
    size++;
}

template <typename T>
T* Stack<T>::pop() {
    if (isEmpty()) return nullptr;

    Node<T>* temp = top;
    T* data = temp->data;
    top = top->next;
    temp->data = nullptr; // Избежать двойного delete
    delete temp;
    size--;
    return data;
}

template <typename T>
void Stack<T>::insert(int index, T* data) {
    if (index < 0 || index > size)
        throw ("Index out of range");

    if (index == 0) {
        push(data);
        return;
    }

    Node<T>* current = top;
    for (int i = 0; i < index - 1; i++)
        current = current->next;

    Node<T>* newNode = new Node<T>(data);
    newNode->next = current->next;
    current->next = newNode;
    size++;
}

template <typename T>
void Stack<T>::removeAt(int index) {
    if (index < 0 || index >= size)
        throw ("Index out of range");

    if (index == 0) {
        pop();
        return;
    }

    Node<T>* current = top;
    for (int i = 0; i < index - 1; i++)
        current = current->next;

    Node<T>* toDelete = current->next;
    current->next = toDelete->next;
    toDelete->data = nullptr; // Чтобы не удалялось в деструкторе
    delete toDelete;
    size--;
}

template <typename T>
int Stack<T>::find(const T& data) const {
    Node<T>* current = top;
    int index = 0;

    while (current != nullptr) {
        if (*current->data == data)  // Сравнение объектов через перегруженный оператор ==
            return index;
        current = current->next;
        index++;
    }

    return -1;
}

template <typename T>
void Stack<T>::display() const {
    Node<T>* current = top;
    while (current != nullptr) {
        if (current->data)
            current->data->print();
        std::cout << std::endl;
        current = current->next;
    }
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return top == nullptr;
}

template <typename T>
int Stack<T>::getSize() const {
    return size;
}


template class Stack<DateTime>;
template class Stack<DateTimeWithTimeZone>;
template class Stack<Timer>;
