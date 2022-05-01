#ifndef UTILITY_RANDOM_HPP
#define UTILITY_RANDOM_HPP

namespace utility {
	namespace random {
		double mt32 (double max, double min = 0, bool inclusive = false);

		double mt64 (double max, double min = 0, bool inclusive = false);
	}
}

#endif