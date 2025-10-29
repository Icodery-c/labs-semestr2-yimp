#include "timer.h"
/*
void Timer::StartTimer () {

  if (!Running) {

    Running = true;
    StartTime = std::chrono::system_clock::now();

  }

}

void Timer::EndTimer () {

  if (Running) {

    Running = false;

    auto EndTime = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(EndTime-StartTime).count();

    *this += DateTime(0,0,0,0,0, static_cast<int>(duration));


  }


}


void Timer::ResetTimer () {

  Running = false;
  *this = DateTime();


}

void Timer::RunningTimer () {

  return Running;


}


int Timer::GetSeconds () {

  if (Running) {

    auto CurrentTime = std::chrono::system_clock::now();
    //return static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(
      //currentTime - startTime).count());

    return std::chrono::duration_cast<std::chrono::seconds>(CurrentTime-StartTime).count();
  }

  return 0;



}


int Timer::GetMilliseconds () {

  if (Running) {

    auto CurrentTime = std::chrono::system_clock::now();

    //return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(
      //currentTime - startTime).count());

    return std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime-StartTime).count();

  }

  return 0;

}


void Timer::WaitTimer(int seconds) {


  std::this_thread::sleep_for(std::chrono::seconds(seconds));

  if (Running) {

    *this += DateTime(0,0,0,0,0 seconds);

  }

}
*/

void Timer::StartTimer() {
    if (!Running) {
        Running = true;
        StartTime = std::chrono::system_clock::now();
    }
}

void Timer::EndTimer() {
    if (Running) {
        Running = false;
    }
}

void Timer::ResetTimer() {
    Running = false;
}

bool Timer::RunningTimer() const {
    return Running;
}

int Timer::GetSeconds() const {
    if (Running) {
        auto CurrentTime = std::chrono::system_clock::now();
        return static_cast<int>(
            std::chrono::duration_cast<std::chrono::seconds>(
                CurrentTime - StartTime
            ).count()
        );
    }
    return 0;
}

void Timer::WaitTimer(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
