
#include "./random.h"
#include <random>


double util::random::mt32 (double max, double min, bool inclusive) {
	static std::mt19937 rng32 (std::random_device {}());
	return rng32() / 2.0 / INT32_MAX * (max - min + inclusive) + min;
}

double util::random::mt64 (double max, double min, bool inclusive) {
	static std::mt19937_64 rng64 (std::random_device {}());
	return rng64() / 2.0 / INT64_MAX * (max - min + inclusive) + min;
}
