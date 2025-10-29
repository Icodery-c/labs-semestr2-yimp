#include "time.h"
#include <iostream>


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





}
