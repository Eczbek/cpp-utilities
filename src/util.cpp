
#include "util.h"
#include <random>
#include <limits>


void util::io::ignore (char until) {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), until);
}

double util::random::get (double max, double min) {
	static std::mt19937 rng32 (std::random_device {} ());
	return rng32() / 2.0 / INT32_MAX * (max - min) + min;
}
