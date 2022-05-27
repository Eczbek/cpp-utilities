#pragma once

#include <string>
#include <termios.h>
#include <thread>
#include <unistd.h>


namespace util {
	namespace io {
		namespace lock {
			struct raw {
				termios cooked;

				raw();

				~raw();
			};

			struct nonblock {
				nonblock();

				~nonblock();
			};
		};

		void ignore(const char until = 0);

		void ignore(std::streamsize characters);

		char char_wait();

		char char_read(const char defaultChar = 0);

		template <typename Duration>
		char char_timeout(const Duration timeout, const char defaultChar = 0, const bool readLast = false) {
			util::io::lock::raw rawLock;
			util::io::lock::nonblock nonblockLock;
			std::this_thread::sleep_for(timeout);
			char input = defaultChar;
			bool ok;
			do
				ok = read(STDIN_FILENO, &input, 1) == 1;
			while (readLast && ok);
			util::io::ignore();
			return input;
		}

		std::string string_read();

		void erase_all();

		void erase_line();

		void style_set(const int style);

		void get_win_size(int& rows, int& cols);

		namespace cursor {
			void get(int& row, int& col);

			void set(const int row, const int col);

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

		enum styles {
			STYLE_RESET = 0,
			STYLE_EF_BOLD,
			STYLE_EF_DIM,
			STYLE_EF_ITALIC,
			STYLE_EF_UNDERLINE,
			STYLE_EF_BLINK,
			STYLE_EF_REVERSE = 7,
			STYLE_EF_HIDDEN,
			STYLE_EF_STRIKETHROUGH,
			STYLE_EF_UNDERLINE_DOUBLE = 21,
			STYLE_FG_BLACK = 30,
			STYLE_FG_RED,
			STYLE_FG_GREEN,
			STYLE_FG_YELLOW,
			STYLE_FG_BLUE,
			STYLE_FG_MAGENTA,
			STYLE_FG_CYAN,
			STYLE_FG_WHITE,
			STYLE_BG_BLACK = 40,
			STYLE_BG_RED,
			STYLE_BG_GREEN,
			STYLE_BG_YELLOW,
			STYLE_BG_BLUE,
			STYLE_BG_MAGENTA,
			STYLE_BG_CYAN,
			STYLE_BG_WHITE,
			STYLE_FG_BLACK_BRIGHT = 90,
			STYLE_FG_RED_BRIGHT,
			STYLE_FG_GREEN_BRIGHT,
			STYLE_FG_YELLOW_BRIGHT,
			STYLE_FG_BLUE_BRIGHT,
			STYLE_FG_MAGENTA_BRIGHT,
			STYLE_FG_CYAN_BRIGHT,
			STYLE_FG_WHITE_BRIGHT,
			STYLE_BG_BLACK_BRIGHT = 100,
			STYLE_BG_RED_BRIGHT,
			STYLE_BG_GREEN_BRIGHT,
			STYLE_BG_YELLOW_BRIGHT,
			STYLE_BG_BLUE_BRIGHT,
			STYLE_BG_MAGENTA_BRIGHT,
			STYLE_BG_CYAN_BRIGHT,
			STYLE_BG_WHITE_BRIGHT
		};
	}
}
