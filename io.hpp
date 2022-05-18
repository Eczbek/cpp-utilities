#pragma once
#include <termios.h>
#include <unistd.h>
#include <thread>
#include <string>

#define AEC_EF_BOLD "\033[1m"
#define AEC_EF_DIM "\033[2m"
#define AEC_EF_ITALIC "\033[3m"
#define AEC_EF_UNDERLINE "\033[4m"
#define AEC_EF_BLINK "\033[5m"
#define AEC_EF_REVERSE "\033[7m"
#define AEC_EF_HIDDEN "\033[8m"
#define AEC_EF_STRIKETHROUGH "\033[9m"
#define AEC_EF_UNDERLINE_DOUBLE "\033[21m"
#define AEC_FG_BLACK "\033[30m"
#define AEC_FG_RED "\033[31m"
#define AEC_FG_GREEN "\033[32m"
#define AEC_FG_YELLOW "\033[33m"
#define AEC_FG_BLUE "\033[34m"
#define AEC_FG_MAGENTA "\033[35m"
#define AEC_FG_CYAN "\033[36m"
#define AEC_FG_WHITE "\033[37m"
#define AEC_FG_BLACK_BRIGHT "\033[90m"
#define AEC_FG_RED_BRIGHT "\033[91m"
#define AEC_FG_GREEN_BRIGHT "\033[92m"
#define AEC_FG_YELLOW_BRIGHT "\033[93m"
#define AEC_FG_BLUE_BRIGHT "\033[94m"
#define AEC_FG_MAGENTA_BRIGHT "\033[95m"
#define AEC_FG_CYAN_BRIGHT "\033[96m"
#define AEC_FG_WHITE_BRIGHT "\033[97m"
#define AEC_BG_BLACK "\033[40m"
#define AEC_BG_RED "\033[41m"
#define AEC_BG_GREEN "\033[42m"
#define AEC_BG_YELLOW "\033[43m"
#define AEC_BG_BLUE "\033[44m"
#define AEC_BG_MAGENTA "\033[45m"
#define AEC_BG_CYAN "\033[46m"
#define AEC_BG_WHITE "\033[47m"
#define AEC_BG_BLACK_BRIGHT "\033[100m"
#define AEC_BG_RED_BRIGHT "\033[101m"
#define AEC_BG_GREEN_BRIGHT "\033[102m"
#define AEC_BG_YELLOW_BRIGHT "\033[103m"
#define AEC_BG_BLUE_BRIGHT "\033[104m"
#define AEC_BG_MAGENTA_BRIGHT "\033[105m"
#define AEC_BG_CYAN_BRIGHT "\033[106m"
#define AEC_BG_WHITE_BRIGHT "\033[107m"
#define AEC_RESET_ALL "\033[0m"
#define AEC_RESET_FG "\033[39m"
#define AEC_RESET_BG "\033[49m"
#define AEC_RESET_EF_BOLD "\033[22m"
#define AEC_RESET_EF_DIM "\033[22m"
#define AEC_RESET_EF_ITALIC "\033[23m"
#define AEC_RESET_EF_UNDERLINE "\033[24m"
#define AEC_RESET_EF_BLINK "\033[25m"
#define AEC_RESET_EF_REVERSE "\033[27m"
#define AEC_RESET_EF_HIDDEN "\033[28m"
#define AEC_RESET_EF_STRIKETHROUGH "\033[29m"
#define AEC_RESET_EF_UNDERLINE_DOUBLE "\033[24m"
#define AEC_ERASE_ALL "\033[2J"
#define AEC_ERASE_LINE "\033[2K"
#define AEC_CURSOR_HIDE "\033[?25l"
#define AEC_CURSOR_SHOW "\033[?25h"

namespace util {
	namespace io {
		class raw_lock {
			private:
				termios cooked;

			public:
				raw_lock ();

				~raw_lock ();
		};

		class nonblock_lock {
			public:
				nonblock_lock ();

				~nonblock_lock ();
		};

		void ignore (const char until = 0);

		char char_wait ();

		char char_read (const char defaultChar = 0);

		template <typename Duration>
		char char_timeout (const Duration timeout, const char defaultChar = 0) {
			std::this_thread::sleep_for(timeout);
			char input = defaultChar;
			util::io::raw_lock rawLock;
			util::io::nonblock_lock nonblockLock;
			while (read(STDIN_FILENO, &input, 1) == 1);
			return input;
		}

		std::string string_read ();

		namespace cursor {
			struct pos {
				int row;
				int col;
			};

			util::io::cursor::pos get_pos ();

			util::io::cursor::pos get_max_pos ();

			void set_pos (const util::io::cursor::pos position);

			enum direction {
				UP = 'A',
				DOWN = 'B',
				RIGHT = 'C',
				LEFT = 'D'
			};

			void move (const char direction, const int count = 1);
		}
	}
}