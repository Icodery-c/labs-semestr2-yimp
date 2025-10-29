#include <chrono>
#include <string>
#include <stdexcept>

class TimeZone {
private:
    std::string timeZone;

public:
    // Конструктор по умолчанию
    TimeZone();

    // Конструктор с параметром
    TimeZone(const std::string& tz);

    std::chrono::zoned_time<std::chrono::system_clock::duration> getCurrentTime() const;

    std::chrono::zoned_time<std::chrono::system_clock::duration>
    fromSystemTime(const std::chrono::system_clock::time_point& sysTime) const;

    const std::string& getName() const;

    void setTimeZone(const std::string& tz);

};
