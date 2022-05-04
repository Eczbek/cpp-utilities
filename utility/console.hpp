#pragma once

#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <thread>
#include <string>
#include <vector>
#include <iostream>

namespace utility {
	namespace console {
		void ignoreLine (char until = '\n');

		void clearScreen ();

		char waitChar (bool echo = true);

		char readChar (bool echo = true);

		template <typename DurationType>
		char readCharTimeout (DurationType timeout, bool echo = true) {
			struct termios cooked, raw;
			tcgetattr(STDIN_FILENO, &cooked);
			raw = cooked;
			raw.c_lflag &= ~ICANON;
			raw.c_lflag &= echo ? ECHO : ~ECHO;
			tcsetattr(STDIN_FILENO, TCSANOW, &raw);
			fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
			std::this_thread::sleep_for(timeout);
			char input;
			while (read(STDIN_FILENO, &input, 1) == 1);
			tcsetattr(STDIN_FILENO, TCSANOW, &cooked);
			return input;
		}

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
