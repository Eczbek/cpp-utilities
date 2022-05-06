#pragma once
	
namespace utility {
	namespace math {
		double wrap (double value, double max, double min = 0);

		bool approxEqual (double value1, double value2, double absoluteEpsilon = 1e-12, double relativeEpsilon = 1e-8);

		int sign (double value);

		double radiansToDegrees (double radians);

		double degreesToRadians (double degrees);
	}
}
