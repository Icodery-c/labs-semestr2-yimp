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
  Date(const Date &other);  //Копирования

  //Геттеры
  int getDay();
  int getMonth();
  int getYear();

  //Сеттеры
  void setDay(int day);
  void setMonth(int month);
  void setYear(int year);

  //Проверка даты
  bool isValidDate(int day, int month, int year);

  // Увеличение
  void increaseDay (int i);
  void increaseMonth (int i);
  void increaseYear (int i);

  // Уменьшение
  void decreaseDay (int i);
  void decreaseMonth (int i);
  void decreaseYear (int i);

  //Вывод в строковом представление
  std::string printDate();


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
  Time(const Time &other);  //Копирования

  //Геттеры
  int getHour();
  int getMinute();
  int getSecond();

  //Сеттеры
  void setHour(int hour);
  void setMinute(int minute);
  void setSecond(int second);

  //Проверка даты
  bool isValidTime(int hour, int minute, int second);

  // Увеличение
  int increaseHour (int i);
  int increaseMinute (int i);
  int increaseSecond (int i);

  // Уменьшение
  int decreaseHour (int i);
  int decreaseMinute (int i);
  int decreaseSecond (int i);

  //Вывод в строковом представление
  std::string printTime();
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

  // Методы доступа (объявления)
  Date& getDate();
  Time& getTime();

  // Константные версии
  const Date& getDate() const;
  const Time& getTime() const;

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
  std::string printDateTime();


};
