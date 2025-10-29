#pragma once
#include <string>
#include <chrono>
#include <thread>
#include <regex>
#include <thread>
#include <stdexcept>

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


  bool operator==(const Date& other) const;


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

  bool operator==(const Time& other) const;

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
  DateTime(int hours, int minutes, int seconds, int day, int month, int year);

  //DateTime(const DateTime &other);
  DateTime(const Date& d, const Time& t);
  DateTime();

  virtual ~DateTime();

  virtual void print() const;

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

  bool operator==(const DateTime& other) const;


};

class DateTimeWithTimeZone : public DateTime {

private:

  std::string timeZone;

public:

  // Конструкторы
  DateTimeWithTimeZone();
  DateTimeWithTimeZone(const std::string& timeZone);
  DateTimeWithTimeZone(const DateTime& dt, const std::string& tz);
  DateTimeWithTimeZone(const Date& d, const Time& t, const std::string& tz);
  DateTimeWithTimeZone(int day, int month, int year,
                        int hour, int minute, int second,
                        const std::string& tz);

  void print() const override;


  std::string getTimeZone() const;
  void setTimeZone(const std::string& tz);

  std::chrono::zoned_time<std::chrono::system_clock::duration> getCurrentTime() const;

  std::chrono::zoned_time<std::chrono::system_clock::duration>
  fromSystemTime(const std::chrono::system_clock::time_point& sysTime) const;

  std::chrono::seconds parseUtcOffset(const std::string& tz) const;

  bool operator==(const DateTimeWithTimeZone& other) const;



};

class Timer : public DateTime {

private:
    std::chrono::time_point<std::chrono::system_clock> startTime;
    bool Running;
    bool autoUpdate;

public:
    // Конструкторы
    Timer();
    Timer(const DateTime& dt);
    Timer(const Date& d, const Time& t, bool running);


    void print() const override;


    // Управление таймером
    void StartTimer();
    void StopTimer();
    void ResetTimer();
    bool RunningTimer() const;

    // Время
    int GetSeconds() const;
    int GetMilliseconds() const;

    void WaitTimer(int seconds);

    // Обновление даты и времени
    void UpdateDateTimeFromNow();

    // Управление флагом автообновления
    void setAutoUpdate(bool enable);
    bool isAutoUpdateEnabled() const;


    bool operator==(const Timer& other) const;
};

template <typename T>

class Node {

public:

    T* data;
    Node<T>* next;

    Node(T* data);
    ~Node();

};

template <typename T>

class Stack {

private:

    Node<T>* top;
    int size;

public:

    Stack();
    ~Stack();

    void push(T* data);
    T* pop();

    void insert(int index, T* data);
    void removeAt(int index);

    int find(const T& data) const;
    void display() const;

    bool isEmpty() const;
    int getSize() const;
};


class DateTimeException : public std::exception {
protected:
    std::string message;
public:
    DateTimeException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
    virtual ~DateTimeException() {}
};

class MemoryException : public DateTimeException {
public:
    MemoryException() : DateTimeException("Memory allocation failed") {}
};

class RangeException : public DateTimeException {
public:
    RangeException(const std::string& msg) : DateTimeException("Out of range: " + msg) {}
};

class InvalidOperationException : public DateTimeException {
public:
    InvalidOperationException(const std::string& msg)
        : DateTimeException("Invalid operation: " + msg) {}
};

class FormatException : public DateTimeException {
public:
    FormatException(const std::string& msg)
        : DateTimeException("Format error: " + msg) {}
};

class FileException : public DateTimeException {
public:
    FileException(const std::string& msg)
        : DateTimeException("File operation failed: " + msg) {}
};
