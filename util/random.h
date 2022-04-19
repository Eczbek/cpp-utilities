#ifndef UTIL_RANDOM_H
#define UTIL_RANDOM_H

namespace util {
	namespace random {
		double mt32 (double max, double min = 0.0, bool inclusive = false);

		double mt64 (double max, double min = 0.0, bool inclusive = false);
	}
}

#endif