#ifndef UTIL_THREAD_HPP
#define UTIL_THREAD_HPP

#include <chrono>
#include <thread>

namespace utility {
	namespace thread {
		template <typename T = std::chrono::milliseconds>
		void sleep (int timeout) {
			std::this_thread::sleep_for(T(timeout));
		}
	}
}

#endif