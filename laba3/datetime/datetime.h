#pragma once
#include <string>

class Date {

private:
  int day;
  int month;
  int year;

public:

  //Конструкторы
  Date();                    //По умолчанию
  Date(int d, int m, int y); //Параметризированный
  Date(const std::string &dateStr);
  Date(const Date &other);  //Копирования

  //Геттеры
  int getDay() const;
  int getMonth() const;
  int getYear() const;

  //Сеттеры
  void setDay(int day);
  void setMonth(int month);
  void setYear(int year);

  //Проверка даты
  bool isValidDate(int day, int month, int year) const;
  int toDays() const;
  void fromDays(int totalDays);
  bool isLeapYear(int year) const;

  // Увеличение
  void increaseDay (int i);
  void increaseMonth (int i);
  void increaseYear (int i);

  // Уменьшение
  void decreaseDay (int i);
  void decreaseMonth (int i);
  void decreaseYear (int i);

  //Перегрузка оператора присвоения
  Date& operator=(const Date& other);

  Date operator+(int day) const;
  Date operator-(int day) const;

  Date& operator+=(int day);
  Date& operator-=(int day);

  Date operator+(const Date& other) const;
  Date operator-(const Date& other) const;

  Date& operator+=(const Date& other);
  Date& operator-=(const Date& other);

  operator char*() const;

  friend std::ostream& operator << (std::ostream &os, const Date &date);

  friend std::istream& operator >> (std::istream& in, Date& date);
  //Вывод в строковом представление
  std::string printDate() const;


};

class Time {

private:
  int hour;
  int minute;
  int second;

public:

  //Конструкторы
  Time();                    //По умолчанию
  Time(int h, int m, int s); //Параметризированный
  Time(const std::string &timeStr);
  Time(const Time &other);  //Копирования

  //Геттеры
  int getHour() const;
  int getMinute() const;
  int getSecond() const;

  //Сеттеры
  void setHour(int hour);
  void setMinute(int minute);
  void setSecond(int second);

  //Проверка даты
  bool isValidTime(int hour, int minute, int second) const;
  int toSeconds() const;
  void fromSeconds(int totalSeconds);

  // Увеличение
  int increaseHour (int i);
  int increaseMinute (int i);
  int increaseSecond (int i);

  // Уменьшение
  int decreaseHour (int i);
  int decreaseMinute (int i);
  int decreaseSecond (int i);

  //Вывод в строковом представление
  std::string printTime() const;

  //Перегрузка оператора присваивания
  Time& operator=(const Time& other);

  Time operator+(int hour) const;
  Time operator-(int hour) const;

  Time& operator+=(int hour);
  Time& operator-=(int hour);

  Time operator+(const Time& other) const;
  Time operator-(const Time& other) const;

  Time& operator+=(const Time& other);
  Time& operator-=(const Time& other);

  operator char*() const;

  friend std::ostream& operator << (std::ostream &os, const Time &time);

  friend std::istream& operator >> (std::istream& in, Time& time);

};

class DateTime  {

friend class Date;
friend class Time;

private:
  Date date;
  Time time;

public:

  // Конструкторы
  //DateTime(); // По умолчанию: 1.1.1 00:00:00

  //DateTime(int day, int month, int year, int hour, int minute, int second);

  //DateTime(const DateTime &other);
  DateTime(const Date& d, const Time& t);
  DateTime();

  // Методы доступа (объявления)
  Date& getDate();
  Time& getTime();

  // Константные версии
  const Date& getDate() const;
  const Time& getTime() const;

  void setTime(const Time& time);
  void setDate(const Date& date);

  // Увеличение
  void increaseHour (int i);
  void increaseMinute (int i);
  void increaseSecond (int i);

  // Уменьшение
  void decreaseHour (int i);
  void decreaseMinute (int i);
  void decreaseSecond (int i);

  // Увеличение
  void increaseDay (int i);
  void increaseMonth (int i);
  void increaseYear (int i);

  // Уменьшение
  void decreaseDay (int i);
  void decreaseMonth (int i);
  void decreaseYear (int i);

  // Вывод даты и времени
  std::string printDateTime() const;

  //Перегрузка оператора присваивания
  DateTime& operator=(const DateTime& other);

  operator char*() const;

  DateTime operator+(int days);
  DateTime operator-(int days);

  DateTime& operator+=(int days);
  DateTime& operator-=(int days);

  DateTime operator+(const DateTime& other) const;
  DateTime operator-(const DateTime& other) const;

  DateTime& operator+=(const DateTime& other);
  DateTime& operator-=(const DateTime& other);

  friend std::ostream& operator << (std::ostream &os, const DateTime &datetime);

  friend std::istream& operator >> (std::istream& in, DateTime& datetime);


};
