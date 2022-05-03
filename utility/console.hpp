#ifndef UTILITY_CONSOLE_HPP
#define UTILITY_CONSOLE_HPP

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace utility {
	namespace console {
		void ignoreLine (char until = '\n');

		char getCharUnix (bool echo = true);

		template <typename StringType = std::string>
		StringType getLineUnix (int characters) {
			StringType line;
			for (int i = 0; i < characters; ++i)
				line += utility::console::getCharUnix(true);
			return line;
		}

		template <typename StringType = std::string>
		StringType getLineUnix (char until) {
			StringType line;
			while (true) {
				char input = utility::console::getCharUnix(true);
				if (input == until)
					return line;
				line += input;
			}
		}

		void clearScreen ();

		template <typename T = std::string>
		T prompt (const std::vector<const std::string_view&>& messages, T defaultValue = T()) {
			T result;
			for (const std::string_view& message : messages) {
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