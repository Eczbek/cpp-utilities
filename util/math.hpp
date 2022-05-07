#pragma once
	
namespace util {
	namespace math {
		template <typename NumberType>
		NumberType wrap (const NumberType value, const NumberType min, const NumberType max) {
			const NumberType diff = max - min;
			return std::fmod(std::fmod(value - min, diff) + diff, diff) + min;
		}

		template <typename NumberType>
		bool approx_eq (const NumberType value1, const NumberType value2, const double absoluteEpsilon = 1e-12, const double relativeEpsilon = 1e-8) {
			return std::abs(value1 - value2) <= std::fmin(absoluteEpsilon, std::fmax(std::abs(value1), std::abs(value2)) * relativeEpsilon);
		}

		template <typename NumberType>
		int sign (const NumberType value) {
			return value > 0
				? 1
				: value < 0
					? -1
					: 0;
		}

		template <typename NumberType>
		NumberType rad_to_deg (const NumberType radians) {
			return radians * 180.0 / M_PI;
		}

		template <typename NumberType>
		NumberType deg_to_rad (const NumberType degrees) {
			return degrees * M_PI / 180.0;
		}
	}
}
