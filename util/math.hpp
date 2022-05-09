#pragma once
#include <cmath>
#include <string_view>

namespace util {
	namespace math {
		template <typename Number>
		Number wrap (const Number value, const Number min, const Number max) {
			const Number diff = max - min;
			return std::fmod(std::fmod(value - min, diff) + diff, diff) + min;
		}

		template <typename Number>
		bool approx_eq (const Number value1, const Number value2, const double absoluteEpsilon = 1e-12, const double relativeEpsilon = 1e-8) {
			return std::abs(value1 - value2) <= std::fmin(absoluteEpsilon, std::fmax(std::abs(value1), std::abs(value2)) * relativeEpsilon);
		}

		template <typename Number>
		int sign (const Number value) {
			return value > 0 ? 1 : value < 0 ? -1 : 0;
		}

		template <typename Number>
		Number rad_to_deg (const Number radians) {
			return radians * 180.0 / M_PI;
		}

		template <typename Number>
		Number deg_to_rad (const Number degrees) {
			return degrees * M_PI / 180.0;
		}

		template <typename Number>
		std::string to_base (const int base, Number value, const std::string_view& digits = "0123456789abcdefghijklmnopqrstuvwxyz") {
			std::string result;
			while (value) {
				result = digits[value % base] + result;
				value /= base;
			}
			return result;
		}

		template <typename Number = int>
		Number from_base (const int base, const std::string& value, const std::string_view& digits = "0123456789abcdefghijklmnopqrstuvwxyz") {
			Number result = 0;
			for (int i = value.length() - 1; i >= 0; --i)
				for (int index = 0; digits[index]; ++index)
					if (digits[index] == value[i]) {
						result += index * std::pow(base, value.length() - i - 1);
						break;
					}
			return result;
		}
	}
}
