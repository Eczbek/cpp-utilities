#include "./math.hpp"

#include <cmath>
#include <algorithm>

double util::math::wrap (const double value, const double min, const double max) {
	const double diff = max - min;
	return std::fmod(std::fmod(value - min, diff) + diff, diff) + min;
}

bool util::math::approx_eq (const double value1, const double value2, const double absoluteEpsilon, const double relativeEpsilon) {
	return std::abs(value1 - value2) <= std::fmin(absoluteEpsilon, std::fmax(std::abs(value1), std::abs(value2)) * relativeEpsilon);
}

int util::math::sign (const double value) {
	return value > 0
		? 1
		: value < 0
			? -1
			: 0;
}

double util::math::rad_to_deg (const double radians) {
	return radians * 180 / M_PI;
}

double util::math::deg_to_rad (const double degrees) {
	return degrees * M_PI / 180;
}
