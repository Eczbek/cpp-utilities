#pragma once

#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <thread>
#include <string>
#include <vector>
#include <iostream>

namespace util {
	namespace io {
		void ignr ();

		void clr_scrn ();

		char char_wait (bool echo = true);

		char char_read (bool echo = true);

		template <typename DurationType>
		char char_read_timeout (const DurationType& timeout, char defaultChar = 0, bool echo = true) {
			termios cooked, raw;
			tcgetattr(STDIN_FILENO, &cooked);
			raw = cooked;
			raw.c_lflag &= ~ICANON;
			raw.c_lflag &= echo ? ECHO : ~ECHO;
			tcsetattr(STDIN_FILENO, TCSANOW, &raw);
			fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
			std::this_thread::sleep_for(timeout);
			char input = defaultChar;
			while (read(STDIN_FILENO, &input, 1) == 1);
			tcsetattr(STDIN_FILENO, TCSANOW, &cooked);
			return input;
		}
	}
}
