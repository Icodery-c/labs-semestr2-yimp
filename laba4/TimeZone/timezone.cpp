#include "timezone.h"
#include <chrono>
#include <string>
#include <stdexcept>


TimeZone::TimeZone() : timeZone("Europe/Moscow") {}

// Конструктор с параметром
TimeZone::TimeZone(const std::string& tz) : timeZone(tz) {
	try {
		// Проверяем валидность часового пояса
		std::chrono::zoned_time{tz, std::chrono::system_clock::now()};
	} catch (const std::exception& e) {
		throw std::runtime_error("Invalid time zone: " + tz);
	}
}


std::chrono::zoned_time<std::chrono::system_clock::duration> TimeZone::getCurrentTime() const {
	return std::chrono::zoned_time{timeZone, std::chrono::system_clock::now()};
}


std::chrono::zoned_time<std::chrono::system_clock::duration>
TimeZone::fromSystemTime(const std::chrono::system_clock::time_point& sysTime) const {
	return std::chrono::zoned_time{timeZone, sysTime};
}


const std::string& TimeZone::getName() const { return timeZone; }


void TimeZone::setTimeZone(const std::string& tz) {
	try {
		std::chrono::zoned_time{tz, std::chrono::system_clock::now()};
		timeZone = tz;
	} catch (const std::exception& e) {
		throw std::runtime_error("Invalid time zone: " + tz);
	}
}
