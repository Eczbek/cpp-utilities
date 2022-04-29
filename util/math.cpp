
#include "./math.h"
#include <cmath>

double util::math::clamp (double value, double max, double min) {
	return std::fmin(std::fmax(value, min), max);
}

double util::math::lerp (double value, double max, double min) {
	return value * (max - min) + min;
}

double util::math::norm (double value, double max, double min) {
	return (value - min) / (max - min);
}

double util::math::wrap (double value, double max, double min) {
	if (!min)
		return std::fmod(value, max);
	int diff = max - min;
	return std::fmod(std::fmod(value - min, diff) + diff, diff) + min;
}

double util::math::round (double value, double interval) {
	return std::round(value / interval) * interval;
}
