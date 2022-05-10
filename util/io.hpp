#pragma once
#include <termios.h>
#include <unistd.h>
#include <thread>

namespace util {
	namespace io {
		class raw {
			private:
				termios cooked;

			public:
				raw (const bool echo = true);

				~raw ();
		};

		class nonblock {
			public:
				nonblock ();

				~nonblock ();
		};

		void ignore (const char until = 0);

		void clear_screen ();

		char char_wait (const bool echo = true);

		char char_read (const bool echo = true, const char defaultChar = 0);

		template <typename Duration>
		char char_timeout (const Duration timeout, const bool echo = true, const char defaultChar = 0) {
			util::io::raw lock1(echo);
			util::io::nonblock lock2();
			std::this_thread::sleep_for(timeout);
			char input = defaultChar;
			while (read(STDIN_FILENO, &input, 1) == 1);
			return input;
		}
	}
}