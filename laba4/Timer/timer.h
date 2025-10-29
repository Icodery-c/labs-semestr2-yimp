#pragma once
#include <chrono>
#include <thread>
/*
class Timer {

private:

  std::chrono::time_point<std::chrono::system_clock> StartTime;
  bool Running;

public:

  //Конструкторы


  void StartTimer (); // Запуск таймера

  void EndTimer (); // Остановка таймера

  void ResetTimer (); // Сброс таймера

  void RunningTimer (); // Проверка таймера

  //double or int?

  int GetSeconds();

  //int GetMilliseconds();

  void WaitTimer (); // Ожидание указанного количества секунд





};
*/


class Timer {

private:

    bool Running;
    std::chrono::time_point<std::chrono::system_clock> StartTime;

public:

    Timer() : Running(false) {}

    void StartTimer();

    void EndTimer();

    void ResetTimer();

    bool RunningTimer() const;

    int GetSeconds() const;

    void WaitTimer(int seconds);

};
