#include <string>

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
