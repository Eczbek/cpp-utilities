#pragma once
#include <termios.h>
#include <unistd.h>
#include <thread>
#include <string>

#define STYLE_RESET 0
#define STYLE_EF_BOLD 1
#define STYLE_EF_DIM 2
#define STYLE_EF_ITALIC 3
#define STYLE_EF_UNDERLINE 4
#define STYLE_EF_BLINK 5
#define STYLE_EF_REVERSE 7
#define STYLE_EF_HIDDEN 8
#define STYLE_EF_STRIKETHROUGH 9
#define STYLE_EF_UNDERLINE_DOUBLE 21
#define STYLE_FG_BLACK 30
#define STYLE_FG_RED 31
#define STYLE_FG_GREEN 32
#define STYLE_FG_YELLOW 33
#define STYLE_FG_BLUE 34
#define STYLE_FG_MAGENTA 35
#define STYLE_FG_CYAN 36
#define STYLE_FG_WHITE 37
#define STYLE_FG_BLACK_BRIGHT 90
#define STYLE_FG_RED_BRIGHT 91
#define STYLE_FG_GREEN_BRIGHT 92
#define STYLE_FG_YELLOW_BRIGHT 93
#define STYLE_FG_BLUE_BRIGHT 94
#define STYLE_FG_MAGENTA_BRIGHT 95
#define STYLE_FG_CYAN_BRIGHT 96
#define STYLE_FG_WHITE_BRIGHT 97
#define STYLE_BG_BLACK 40
#define STYLE_BG_RED 41
#define STYLE_BG_GREEN 42
#define STYLE_BG_YELLOW 43
#define STYLE_BG_BLUE 44
#define STYLE_BG_MAGENTA 45
#define STYLE_BG_CYAN 46
#define STYLE_BG_WHITE 47
#define STYLE_BG_BLACK_BRIGHT 100
#define STYLE_BG_RED_BRIGHT 101
#define STYLE_BG_GREEN_BRIGHT 102
#define STYLE_BG_YELLOW_BRIGHT 103
#define STYLE_BG_BLUE_BRIGHT 104
#define STYLE_BG_MAGENTA_BRIGHT 105
#define STYLE_BG_CYAN_BRIGHT 106
#define STYLE_BG_WHITE_BRIGHT 107

namespace util {
	namespace io {
		class lock_raw {
			private:
				termios cooked;

			public:
				lock_raw ();

				~lock_raw ();
		};

		class lock_nonblock {
			public:
				lock_nonblock ();

				~lock_nonblock ();
		};

		void ignore (const char until = 0);

		char char_wait ();

		char char_read (const char defaultChar = 0);

		template <typename Duration>
		char char_timeout (const Duration timeout, const char defaultChar = 0) {
			util::io::lock_raw rawLock;
			util::io::lock_nonblock nonblockLock;
			std::this_thread::sleep_for(timeout);
			char input = defaultChar;
			while (read(STDIN_FILENO, &input, 1) == 1);
			return input;
		}

		std::string string_read (const int chunkSize = 1);

		void erase_all ();

		void erase_line ();

		void style_set (const int style);

		void get_win_size (int& rows, int& cols);

		namespace cursor {
			void get_pos (int& row, int& col);

			void set_pos (const int row, const int col);

			enum direction {
				UP = 'A',
				DOWN = 'B',
				RIGHT = 'C',
				LEFT = 'D'
			};

			void move (const char direction, const int count = 1);

			void hide ();

			void show ();
		}
	}
}