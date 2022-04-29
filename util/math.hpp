#ifndef UTIL_MATH_H
#define UTIL_MATH_H

namespace util {
	namespace math {
		double clamp (double value, double max, double min = 0);

		double lerp (double value, double max, double min = 0);

		double norm (double value, double max, double min = 0);

		double wrap (double value, double max, double min = 0);

		double round (double value, double interval);
	}
}

#endif