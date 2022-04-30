#ifndef UITL_TIME_HPP
#define UTIL_TIME_HPP

#include <chrono>
#include <string>

#define HOURS_BEFORE_EPOCH 17268648

namespace util {
	namespace time {
		std::string MONTH_NAMES[] { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		std::string WEEKDAY_NAMES[] { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

		template <typename T = std::chrono::milliseconds>
		long now () {
			return std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		}
	}
}

#endif