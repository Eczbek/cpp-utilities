#pragma once

#include <fcntl.h>
#include <string>
#include <termios.h>
#include <thread>
#include <unistd.h>


namespace util {
	namespace io {
		class raw {
		private:
			termios cooked;

		public:
			raw(const bool echo = false);

			~raw();
		};

		class nonblock {
		private:
			const int blocking = fcntl(STDIN_FILENO, F_GETFL);

		public:
			nonblock();

			~nonblock();
		};

		void ignore(const char until = 0);

		void ignore(std::streamsize characters);

		char wait_char(const bool echo = false);

		char read_char(const char defaultChar = 0);

		template <typename Duration>
		char timeout_char(const Duration timeout, const char defaultChar = 0, const bool echo = false, const bool getLast = true) {
			util::io::raw rawLock(echo);
			util::io::nonblock nonblockLock;
			std::this_thread::sleep_for(timeout);
			char input = defaultChar;
			while (read(STDIN_FILENO, &input, 1) == 1 && getLast);
			return input;
		}

		std::string read_string();

		void erase_all();

		void erase_line();

		struct pos {
			int row;
			int col;
		};

		util::io::pos get_win_size();

		namespace cursor {
			util::io::pos get();

			void set(const util::io::pos position);

			enum: char {
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
