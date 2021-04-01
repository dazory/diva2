#ifndef TIMER_H
#define TIMER_H
// Timer related
#include <sys/time.h>
#include <chrono>

// Current time since epoch in microseconds
inline long get_time_since_epoch_count() {
  auto now = std::chrono::system_clock::now();
  auto now_ms = std::chrono::time_point_cast<std::chrono::microseconds>(now);
  long cur_time = now_ms.time_since_epoch().count();
  return cur_time;
}

// It is a stopwatch which ticks and tocks
template<typename T>
class Timer {
 public:
  Timer() {
    tick();
  }

  void tick() {
    begin_time = std::chrono::steady_clock::now();
  }

  void tock() {
    time_elapsed = std::chrono::duration_cast<T>(std::chrono::steady_clock::now() - begin_time);
  }

  long tock_count() {
    time_elapsed = std::chrono::duration_cast<T>(std::chrono::steady_clock::now() - begin_time);
    return long(time_elapsed.count());
  }

  T get_duration() const {
    return time_elapsed;
  }

  std::chrono::time_point<std::chrono::steady_clock> get_starttime() const {
    return begin_time;
  }

 private:
  std::chrono::time_point<std::chrono::steady_clock> begin_time;

  T time_elapsed;
};

typedef Timer<std::chrono::microseconds> TimerMicroSecconds;

#endif
