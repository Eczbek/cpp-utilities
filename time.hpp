#pragma once
#include <chrono>
#include <string_view>
#include <array>

namespace util {
	namespace time {
		constexpr int HOURS_BEFORE_EPOCH = 17268648;

		constexpr std::array<std::string_view, 12> MONTH_NAMES { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		constexpr std::array<std::string_view, 7> WEEKDAY_NAMES { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

		template <typename Duration = std::chrono::nanoseconds>
		long now () {
			return std::chrono::duration_cast<Duration>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		}
	}
}
