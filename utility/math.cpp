#include "./math.hpp"

#include <cmath>

double utility::math::clamp (double value, double max, double min) {
	return value > max
		? max
		: value < min
			? min
			: value;
}

double utility::math::lerp (double value, double max, double min) {
	return value * (max - min) + min;
}

double utility::math::norm (double value, double max, double min) {
	return (value - min) / (max - min);
}

double utility::math::wrap (double value, double max, double min) {
	if (!min)
		return std::fmod(value, max);
	int diff = max - min;
	return std::fmod(std::fmod(value - min, diff) + diff, diff) + min;
}

double utility::math::round (double value, double interval) {
	return std::round(value / interval) * interval;
}

bool utility::math::approxEqual (double value1, double value2, double absoluteEpsilon, double relativeEpsilon) {
	return std::abs(value1 - value2) <= std::fmin(absoluteEpsilon, std::fmax(std::abs(value1), std::abs(value2)) * relativeEpsilon);
}

int utility::math::sign (double value) {
	return utility::math::clamp(value, 1, -1);
}

double utility::math::radiansToDegrees (double radians) {
	return radians * 180 / M_PI;
}

double utility::math::degreesToRadians (double degrees) {
	return degrees * M_PI / 180;
}
