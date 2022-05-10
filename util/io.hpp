#pragma once
#include <termios.h>
#include <unistd.h>
#include <thread>

namespace util {
	namespace io {
		class raw_lock {
			private:
				termios cooked;

			public:
				raw_lock (const bool echo = true);

				~raw_lock ();
		};

		class nonblock_lock {
			public:
				nonblock_lock ();

				~nonblock_lock ();
		};

		void ignore (const char until = 0);

		void clear_screen ();

		char char_wait (const bool echo = true);

		char char_read (const bool echo = true, const char defaultChar = 0);

		template <typename Duration>
		char char_timeout (const Duration timeout, const bool echo = true, const char defaultChar = 0) {
			util::io::raw_lock rawLock(echo);
			util::io::nonblock_lock nonblockLock;
			std::this_thread::sleep_for(timeout);
			char input = defaultChar;
			while (read(STDIN_FILENO, &input, 1) == 1);
			return input;
		}
	}
}