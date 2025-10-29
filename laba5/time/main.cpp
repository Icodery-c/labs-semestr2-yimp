#include "time.h"
#include <iostream>
#include <vector>
#include <fstream>

void writeBinaryFile(const std::string& filename, const std::vector<Time>& times) {
    std::ofstream out(filename, std::ios::binary);
    if (out.is_open()) {
        size_t size = times.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        out.write(reinterpret_cast<const char*>(times.data()), size * sizeof(Time));
        out.close();
    }
}

void readBinaryFile(const std::string& filename, std::vector<Time>& times) {
    std::ifstream in(filename, std::ios::binary);
    if (in.is_open()) {
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        times.resize(size);
        in.read(reinterpret_cast<char*>(times.data()), size * sizeof(Time));
        in.close();
    }
}

int main () {


  Time time1;
  std::cout << time1.getHour() << ":" << time1.getMinute() << ":" << time1.getSecond() << std::endl << std::endl;

  Time time2(23,59,59);
  std::cout << time2.getHour() << ":" << time2.getMinute() << ":" << time2.getSecond() << std::endl << std::endl;

  Time time3(time2);
  std::cout << time3.getHour() << ":" << time3.getMinute() << ":" << time3.getSecond() << std::endl << std::endl;

  Time time4(23,59,59);

  std::cout << time4.getHour() << ":" << time4.getMinute() << ":" << time4.getSecond() << std::endl << std::endl;

  time4.increaseHour(49);
  std::cout << time4.getHour() << ":" << time4.getMinute() << ":" << time4.getSecond() << std::endl << std::endl;
  //time4.increaseMinute(1);
  //std::cout << time4.getHour() << ":" << time4.getMinute() << ":" << time4.getSecond() << std::endl << std::endl;

  //time4.increaseSecond(1);
  //std::cout << time4.getHour() << ":" << time4.getMinute() << ":" << time4.getSecond() << std::endl << std::endl;


  //time4.decreaseHour(1);
  //std::cout << time4.getHour() << ":" << time4.getMinute() << ":" << time4.getSecond() << std::endl << std::endl;

  //time4.decreaseMinute(1);
  //std::cout << time4.getHour() << ":" << time4.getMinute() << ":" << time4.getSecond() << std::endl << std::endl;

  time4.decreaseSecond(1);

  std::cout << time4.printTime() << std:: endl;


  Time t("23:59:59");
  std::cout << t.getHour() << ":" << t.getMinute() << ":" << t.getSecond() << std::endl << std::endl;

  t.increaseSecond(1);

  std::cout << t.getHour() << ":" << t.getMinute() << ":" << t.getSecond() << std::endl << std::endl;

  t = t + 24;

  std::cout << t.getHour() << ":" << t.getMinute() << ":" << t.getSecond() << std::endl << std::endl;

  t = t - 20;

  std::cout << t.getHour() << ":" << t.getMinute() << ":" << t.getSecond() << std::endl << std::endl;


  Time t1(13,13,13);
  Time t2(12,12,12);

  Time t3 = t1+t2;


  Time time(23,59,59);

  std:: cout << time << std::endl;

  Time ttt;

  std::cin >> ttt;

  std::cout << ttt << std:: endl;

std::vector<Time> times = {
      Time(20, 0, 0),
      Time(21, 12, 0),
      Time(22, 12, 0),
      Time(23, 12, 0),
      Time(0, 0, 0)
  };

  std::ofstream out("times.txt");


  if (out.is_open()) {
      for (const Time& time : times) {
          out << time << std::endl;
      }

  }
  out.close();


  std::vector<Time> new_times;

  std::ifstream in("times.txt");

  if (in.is_open()) {
      Time time(0, 0, 0);
      while (in >> time) {
          new_times.push_back(time);
      }
  }
  in.close();


  std::cout << "All times: " << std::endl;
  for (const Time& time : new_times) {
      std::cout << time << std::endl;
  }

  std::vector<Time> timesbinary = {
      Time(20, 0, 0),
      Time(21, 12, 0),
      Time(22, 12, 0),
      Time(23, 12, 0),
      Time(0, 0, 0)
    };

    writeBinaryFile("times.bin", timesbinary);

    std::vector<Time> new_timesbinary;
    readBinaryFile("times.bin", new_timesbinary);

    std::cout << "All times: " << std::endl;
    for (const Time& time : new_timesbinary) {
        std::cout << time << std::endl;
    }

    return 0;
}
