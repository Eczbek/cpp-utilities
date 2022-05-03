#ifndef UTILITY_MATH_HPP
#define UTILITY_MATH_HPP
	
namespace utility {
	namespace math {
		double clamp (double value, double max, double min = 0);

		double lerp (double value, double max, double min = 0);

		double norm (double value, double max, double min = 0);

		double wrap (double value, double max, double min = 0);

		double round (double value, double interval = 1);

		bool approxEqual (double value1, double value2, double absoluteEpsilon = 1e-12, double relativeEpsilon = 1e-8);

		int sign (double value);

		double radiansToDegrees (double radians);

		double degreesToRadians (double degrees);
	}
}

#endif