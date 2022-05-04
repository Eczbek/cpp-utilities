#ifndef UTILITY_CONSOLE_HPP
#define UTILITY_CONSOLE_HPP

#include <iostream>
#include <string>
#include <vector>

namespace utility {
	namespace console {
		void ignoreLine (char until = '\n');

		void clearScreen ();

		char waitChar (bool echo = true);

		char readChar (bool echo = true);

		template <typename InputType, typename MessageType = std::string>
		InputType prompt (const std::vector<const MessageType&>& messages, const InputType& defaultValue = InputType()) {
			InputType result;
			for (const MessageType& message : messages) {
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