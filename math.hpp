#pragma once

#include <array>
#include <cmath>
#include <limits>
#include <numbers>
#include <string>
#include <string_view>


namespace util {
	namespace math {
		template <typename Number>
		Number wrap(const Number value, const Number min, const Number max) {
			const Number diff = max - min;
			return std::fmod(std::fmod(value - min, diff) + diff, diff) + min;
		}

		template <typename Number>
		bool approx_equal(const Number value1, const Number value2, const int precision = 12) {
			return std::fabs(value1 - value2) <= std::numeric_limits<Number>::epsilon() * std::fabs(value1 + value2) * precision || std::fabs(value1 - value2) < std::numeric_limits<Number>::min();
		}

		template <typename Number>
		int sign(const Number value) {
			return value > 0
				? 1
				: value < 0
					? -1
					: 0;
		}

		template <typename Result = double, typename Number>
		Result rad_to_deg(const Number radians) {
			return radians * 180 / std::numbers::pi;
		}

		template <typename Result = double, typename Number>
		Result deg_to_rad(const Number degrees) {
			return degrees * std::numbers::pi / 180;
		}

		template <typename Number>
		std::string base_to(Number value, const int base, const std::string_view& digits = "0123456789abcdefghijklmnopqrstuvwxyz") {
			std::string result;
			while (value) {
				result = digits[value % base] + result;
				value /= base;
			}
			return result;
		}

		template <typename Number = int>
		Number base_from(const std::string_view& value, const int base, const std::string_view& digits = "0123456789abcdefghijklmnopqrstuvwxyz") {
			std::array<int, std::numeric_limits<char>::max() - std::numeric_limits<char>::min() + 1> digitsMap;
			const auto getIndex = [&](const char digit) -> int& {
				return digitsMap[digit - std::numeric_limits<char>::min()];
			};
			for (std::size_t i = 0; i < digits.length(); ++i)
				getIndex(digits[i]) = i;
			Number result = 0;
			int power = 1;
			for (std::size_t i = value.length(); i > 0; --i) {
				result += getIndex(value[i - 1]) * power;
				power *= base;
			}
			return result;
		}
	}
}
