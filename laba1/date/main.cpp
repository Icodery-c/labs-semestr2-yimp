#include <iostream>
#include "date.h"

int main () {

    //Проверка конструкторов и геттера

    Date date1;
    std::cout << date1.getDay() << "." << date1.getMonth() << "." << date1.getYear() << std::endl << std::endl;

    Date date2(31,12,2025);
    std::cout << date2.getDay() << "." << date2.getMonth() << "." << date2.getYear() << std::endl << std::endl;

    Date date3(date2);
    std::cout << date3.getDay() << "." << date3.getMonth() << "." << date3.getYear() << std::endl << std::endl;

    // Проверка сеттеров

    date3.setDay(12);
    date3.setMonth(3);
    date3.setYear(2026);

    std::cout << date3.getDay() << "." << date3.getMonth() << "." << date3.getYear() << std::endl << std::endl;

    Date date4(31,12,2024);
    std::cout << date4.getDay() << "." << date4.getMonth() << "." << date4.getYear() << std::endl << std::endl;

    date4.setDay(31);
    date4.setMonth(12);
    date4.setYear(2025);

    std::cout << date4.getDay() << "." << date4.getMonth() << "." << date4.getYear() << std::endl << std::endl;

    date4.increaseDay(1);
    std::cout << date4.getDay() << "." << date4.getMonth() << "." << date4.getYear() << std::endl << std::endl;

    date4.increaseMonth(1);
    std::cout << date4.getDay() << "." << date4.getMonth() << "." << date4.getYear() << std::endl << std::endl;

    date4.increaseYear(1);
    std::cout << date4.getDay() << "." << date4.getMonth() << "." << date4.getYear() << std::endl << std::endl;

    date4.decreaseDay(1);
    std::cout << date4.getDay() << "." << date4.getMonth() << "." << date4.getYear() << std::endl << std::endl;

    date4.decreaseMonth(1);
    std::cout << date4.getDay() << "." << date4.getMonth() << "." << date4.getYear() << std::endl << std::endl;

    date4.decreaseYear(1);
    std::cout << date4.getDay() << "." << date4.getMonth() << "." << date4.getYear() << std::endl << std::endl;

    std::cout << date4.printDate() << std::endl << std::endl;





  return 0;



}
