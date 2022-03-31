#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <thread>
#include <chrono>


namespace util {
	namespace io {
		void ignore (char until = '\n');

		template <typename inputType>
		inputType prompt (std::string message = "") {
			inputType value;
			while (true) {
				std::cout << message;
				std::cin >> value;
				if (!std::cin.fail()) return value;
				std::cin.clear();
				util::io::ignore();
			}
		}
	}

	namespace rand {
		double get (double max, double min = 0.0);
	}

	namespace time {
		template <typename duration = std::chrono::milliseconds>
		long now () {
			return std::chrono::duration_cast<duration>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		}
	}
}

#endif