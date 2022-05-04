#pragma once

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
			InputType input;
			for (const MessageType& message : messages) {
				std::cout << message;
				std::cin >> input;
				if (!std::cin.fail())
					return input;
				std::cin.clear();
				utility::console::ignoreLine();
			}
			return defaultValue;
		}
	}
}
