#ifndef UTILITY_THREAD_HPP
#define UTILITY_THREAD_HPP

#include <chrono>
#include <thread>

namespace utility {
	namespace thread {
		template <typename DurationType = std::chrono::milliseconds>
		void sleep (int timeout) {
			std::this_thread::sleep_for(DurationType(timeout));
		}
	}
}

#endif