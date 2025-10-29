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
  void increaseHour (int i);
  void increaseMinute (int i);
  void increaseSecond (int i);

  // Уменьшение
  void decreaseHour (int i);
  void decreaseMinute (int i);
  void decreaseSecond (int i);

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



};
