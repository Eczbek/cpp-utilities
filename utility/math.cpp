#include "./math.hpp"

#include <cmath>
#include <algorithm>

double utility::math::wrap (double value, double max, double min) {
	if (!min)
		return std::fmod(value, max);
	int diff = max - min;
	return std::fmod(std::fmod(value - min, diff) + diff, diff) + min;
}

bool utility::math::approxEqual (double value1, double value2, double absoluteEpsilon, double relativeEpsilon) {
	return std::abs(value1 - value2) <= std::fmin(absoluteEpsilon, std::fmax(std::abs(value1), std::abs(value2)) * relativeEpsilon);
}

int utility::math::sign (double value) {
	return value > 0
		? 1
		: value < 0
			? -1
			: 0;
}

double utility::math::radiansToDegrees (double radians) {
	return radians * 180 / M_PI;
}

double utility::math::degreesToRadians (double degrees) {
	return degrees * M_PI / 180;
}
