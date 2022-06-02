#pragma once

#include <string>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <util/misc.hpp>


namespace util {
	namespace io {
		class raw {
		private:
			termios cooked;

		public:
			raw();

			~raw();
		};

		struct nonblock {
			nonblock();

			~nonblock();
		};

		void ignore(const char until = 0);

		void ignore(std::streamsize characters);

		char wait_char();

		char read_char(const char defaultChar = 0);

		template <typename Duration>
		char timeout_char(const Duration timeout, const char defaultChar = 0, const bool readLast = false) {
			util::io::raw rawLock;
			util::io::nonblock nonblockLock;
			std::this_thread::sleep_for(timeout);
			char input = defaultChar;
			bool ok;
			do
				ok = read(STDIN_FILENO, &input, 1) == 1;
			while (readLast && ok);
			util::io::ignore();
			return input;
		}

		std::string read_string();

		void erase_all();

		void erase_line();

		util::pos get_win_size();

		namespace cursor {
			util::pos get();

			void set(const util::pos position);

			enum directions: char {
				UP = 'A',
				DOWN,
				RIGHT,
				LEFT
			};

			void move(const char direction, const int count = 1);

			void hide();

			void show();
		}

		struct style {
			style(const int style);

			~style();

			enum {
				NONE = 0,
				EF_BOLD,
				EF_DIM,
				EF_ITALIC,
				EF_UNDERLINE,
				EF_BLINK,
				EF_REVERSE = 7,
				EF_HIDDEN,
				EF_STRIKETHROUGH,
				EF_UNDERLINE_DOUBLE = 21,
				FG_BLACK = 30,
				FG_RED,
				FG_GREEN,
				FG_YELLOW,
				FG_BLUE,
				FG_MAGENTA,
				FG_CYAN,
				FG_WHITE,
				BG_BLACK = 40,
				BG_RED,
				BG_GREEN,
				BG_YELLOW,
				BG_BLUE,
				BG_MAGENTA,
				BG_CYAN,
				BG_WHITE,
				FG_BLACK_BRIGHT = 90,
				FG_RED_BRIGHT,
				FG_GREEN_BRIGHT,
				FG_YELLOW_BRIGHT,
				FG_BLUE_BRIGHT,
				FG_MAGENTA_BRIGHT,
				FG_CYAN_BRIGHT,
				FG_WHITE_BRIGHT,
				BG_BLACK_BRIGHT = 100,
				BG_RED_BRIGHT,
				BG_GREEN_BRIGHT,
				BG_YELLOW_BRIGHT,
				BG_BLUE_BRIGHT,
				BG_MAGENTA_BRIGHT,
				BG_CYAN_BRIGHT,
				BG_WHITE_BRIGHT
			};
		};
	}
}
