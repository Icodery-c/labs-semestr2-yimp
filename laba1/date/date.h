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
