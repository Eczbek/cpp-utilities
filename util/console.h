#ifndef UTIL_CONSOLE_H
#define UTIL_CONSOLE_H

#include <iostream>
#include <string>

namespace util {
	namespace console {
		void ignoreLine (char until = '\n');

		template <typename T = std::string>
		T prompt (const std::string& message = "", const T& defaultValue = T(), int attempts = 1) {
			for (int i = 0; i < attempts; ++i) {
				std::cout << message;
				T result;
				std::cin >> result;
				if (!std::cin.fail()) {
					return result;
				}
				std::cout.clear();
				util::console::ignoreLine();
			}
			return defaultValue;
		}
	}
}

#endif