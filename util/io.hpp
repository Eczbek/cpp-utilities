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
				raw ();

				~raw ();
		};

		void nonblock ();

		void ignr ();

		void clr_scrn ();

		char char_wait ();

		char char_read ();

		template <typename DurationType>
		char char_read_timeout (const DurationType& timeout, const char defaultChar = 0) {
			util::io::raw();
			util::io::nonblock();
			std::this_thread::sleep_for(timeout);
			char input = defaultChar;
			while (read(STDIN_FILENO, &input, 1) == 1);
			return input;
		}
	}
}