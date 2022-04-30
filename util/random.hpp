#ifndef UTIL_RANDOM_HPP
#define UTIL_RANDOM_HPP

namespace util {
	namespace random {
		double mt32 (double max, double min = 0, bool inclusive = false);

		double mt64 (double max, double min = 0, bool inclusive = false);
	}
}

#endif