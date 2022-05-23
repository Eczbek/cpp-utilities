#pragma once

#include <array>
#include <chrono>
#include <string_view>


namespace util {
	namespace time {
		constexpr std::array<std::string_view, 12> MONTHS { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		constexpr std::array<std::string_view, 12> MONTHS_SHORT { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		constexpr std::array<std::string_view, 7> WEEK_DAYS { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
		constexpr std::array<std::string_view, 7> WEEK_DAYS_SHORT { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

		template <typename Duration = std::chrono::nanoseconds>
		long now () {
			return std::chrono::duration_cast<Duration>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		}
	}
}
