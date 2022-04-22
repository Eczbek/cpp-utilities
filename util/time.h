#ifndef UITL_TIME_H
#define UTIL_TIME_H

#include <chrono>

namespace util {
	namespace time {
		template <typename T = std::chrono::milliseconds>
		long now () {
			return std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		}
	}
}

#endif