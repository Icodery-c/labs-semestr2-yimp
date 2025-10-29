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
