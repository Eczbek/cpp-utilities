#ifndef UTIL_CONSOLE_H
#define UTIL_CONSOLE_H

#include <iostream>
#include <string>

namespace util {
	namespace console {
		void ignoreLine (char until = '\n');

		template <typename T>
		T prompt (std::string message = "", bool attempts = 1, T defaultValue = T()) {
			for (T result, int i = 0; i < attempts; ++i) {
				std::cout << message;
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