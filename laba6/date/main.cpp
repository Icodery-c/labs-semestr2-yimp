#include <iostream>
#include "date.h"
#include <fstream>
#include <vector>

void writeBinaryFile(const std::string& filename, const std::vector<Date>& dates) {
    std::ofstream out(filename, std::ios::binary);
    if (out.is_open()) {
        size_t size = dates.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        out.write(reinterpret_cast<const char*>(dates.data()), size * sizeof(Date));
        out.close();
    }
}

void readBinaryFile(const std::string& filename, std::vector<Date>& dates) {
    std::ifstream in(filename, std::ios::binary);
    if (in.is_open()) {
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        dates.resize(size);
        in.read(reinterpret_cast<char*>(dates.data()), size * sizeof(Date));
        in.close();
    }
}


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

    std::cout << "checker" << std::endl;
    Date date5("01.01.01");

    std::cout << date5.getDay() << "." << date5.getMonth() << "." << date5.getYear() << std::endl << std::endl;

    std::cout << date5.printDate() << std::endl << std::endl;

    Date dt1(31,12,2025);
    std::cout << dt1.printDate() << std::endl << std::endl;

    Date dt2(30,1,1);
    std::cout << dt2.printDate() << std::endl << std::endl;

    Date dt3 = dt1 + dt2;

    std::cout << dt3.printDate() << std::endl << std::endl;

    std::vector<Date> dates = {
        Date(31, 12, 2024),
        Date(31, 12, 2025),
        Date(31, 12, 2026),
        Date(31, 12, 2027),
        Date(31, 12, 2028)
    };

    std::ofstream out("dates.txt");


    if (out.is_open()) {
        for (const Date& date : dates) {
            out << date << std::endl;
        }

    }
    out.close();


    std::vector<Date> new_dates;

    std::ifstream in("dates.txt");

    if (in.is_open()) {
        Date date(1, 1, 1);
        while (in >> date) {
            new_dates.push_back(date);
        }
    }
    in.close();


    std::cout << "All dates: " << std::endl;
    for (const Date& date : new_dates) {
        std::cout << date << std::endl;
    }

    std::vector<Date> datesbinary = {
          Date(31, 12, 2024),
          Date(31, 12, 2025),
          Date(31, 12, 2026),
          Date(31, 12, 2027),
          Date(31, 12, 2028)
      };

      writeBinaryFile("dates.bin", datesbinary);

      std::vector<Date> new_datesbinary;
      readBinaryFile("dates.bin", new_datesbinary);

      std::cout << "All dates: " << std::endl;
      for (const Date& date : new_datesbinary) {
          std::cout << date << std::endl;
      }


  return 0;

}
