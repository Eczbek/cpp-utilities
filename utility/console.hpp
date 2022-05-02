#ifndef UTILITY_CONSOLE_HPP
#define UTILITY_CONSOLE_HPP

#include <iostream>
#include <string>
#include <vector>

namespace utility {
	namespace console {
		void ignoreLine (char until = '\n');

		char getCharUnix (bool echo = true);

		void clearScreen ();

		template <typename T = std::string>
		T prompt (const std::vector<std::string>& messages, T defaultValue = T()) {
			T result;
			for (const std::string& message : messages) {
				std::cout << message;
				std::cin >> result;
				if (!std::cin.fail())
					return result;
				std::cin.clear();
				utility::console::ignoreLine();
			}
			return defaultValue;
		}
	}
}

#endif