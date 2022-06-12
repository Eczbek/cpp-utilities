#pragma once

#include <cmath>
#include <numbers>
#include <string>
#include <string_view>
#include <util/map.hpp>


namespace util {
	namespace math {
		template <typename Number>
		Number wrap(const Number value, const Number min, const Number max) {
			const Number diff = max - min;
			return std::fmod(std::fmod(value - min, diff) + diff, diff) + min;
		}

		template <typename Number>
		bool approxEqual(const Number value1, const Number value2, const int precision = 12) {
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
		Result radToDeg(const Number radians) {
			return radians * 180 / std::numbers::pi;
		}

		template <typename Result = double, typename Number>
		Result degToRad(const Number degrees) {
			return degrees * std::numbers::pi / 180;
		}

		template <typename Number>
		std::string baseTo(Number value, const int base, const std::string_view& digits = "0123456789abcdefghijklmnopqrstuvwxyz") {
			std::string result;
			while (value) {
				result = digits[value % base] + result;
				value /= base;
			}
			return result;
		}

		template <typename Number = int>
		Number baseFrom(const std::string_view& value, const int base, const std::string_view& digits = "0123456789abcdefghijklmnopqrstuvwxyz") {
			util::OrderedMap<char, std::size_t> charMap;
			for (std::size_t i = 0; i < digits.size(); ++i)
				charMap[digits[i]] = i;
			Number result = 0;
			Number currentBase = 1;
			for (std::size_t i = value.size(); i > 0; --i) {
				result += charMap[value[i - 1]] * currentBase;
				currentBase *= base;
			}
			return result;
		}
	}
}
