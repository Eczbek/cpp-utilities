#pragma once

#include <cmath>
#include <numbers>
#include <util/str>


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
			util::str::char_map digitsMap(digits);
			Number result = 0;
			int power = 1;
			for (std::size_t i = value.length(); i > 0; --i) {
				result += digitsMap[value[i - 1]] * power;
				power *= base;
			}
			return result;
		}
	}
}
