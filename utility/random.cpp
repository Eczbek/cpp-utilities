#include "./random.hpp"

#include <random>

double utility::random::mt32 (double max, double min, bool inclusive) {
	static std::mt19937 rng32(std::random_device {}());
	return std::uniform_real_distribution<>(min, max + inclusive)(rng32);
}

double utility::random::mt64 (double max, double min, bool inclusive) {
	static std::mt19937_64 rng64(std::random_device {}());
	return std::uniform_real_distribution<>(min, max + inclusive)(rng64);
}
