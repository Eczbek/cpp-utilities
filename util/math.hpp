#pragma once
	
namespace util {
	namespace math {
		double wrap (const double value, const double min, const double max);

		bool approx_eq (const double value1, const double value2, const double absoluteEpsilon = 1e-12, const double relativeEpsilon = 1e-8);

		int sign (const double value);

		double rad_to_deg (const double radians);

		double deg_to_rad (const double degrees);
	}
}
