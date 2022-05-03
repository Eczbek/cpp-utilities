#ifndef UTILITY_TIME_HPP
#define UTILITY_TIME_HPP

#include <chrono>
#include <string_view>
#include <array>

namespace utility {
	namespace time {
		constexpr int HOURS_BEFORE_EPOCH = 17268648;

		constexpr std::array<std::string_view, 12> MONTH_NAMES { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		constexpr std::array<std::string_view, 7> WEEKDAY_NAMES { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

		template <typename DurationType = std::chrono::milliseconds>
		long now () {
			return std::chrono::duration_cast<DurationType>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		}
	}
}

#endif