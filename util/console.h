#ifndef UTIL_CONSOLE_H
#define UTIL_CONSOLE_H

#include <iostream>
#include <string>


namespace util {
	namespace console {
		void ignoreLine (char until = '\n');

		template <typename T>
		T prompt (std::string message = "", bool repeatIfFail = false, T defaultValue = T()) {
			T result;
			do {
				std::cout << message;
				std::cin >> result;
				if (!std::cin.fail()) {
					return result;
				}
				util::console::ignoreLine();
			} while (repeatIfFail);
			return defaultValue;
		}
	}
}

#endif