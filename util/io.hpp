#pragma once
#include <termios.h>
#include <unistd.h>
#include <thread>

#define ANSI_EF_BOLD "\033[1m"
#define ANSI_EF_DIM "\033[2m"
#define ANSI_EF_ITALIC "\033[3m"
#define ANSI_EF_UNDERLINE "\033[4m"
#define ANSI_EF_BLINK "\033[5m"
#define ANSI_EF_REVERSE "\033[7m"
#define ANSI_EF_HIDDEN "\033[8m"
#define ANSI_EF_STRIKETHROUGH "\033[9m"
#define ANSI_EF_UNDERLINE_DOUBLE "\033[21m"
#define ANSI_FG_BLACK "\033[30m"
#define ANSI_FG_RED "\033[31m"
#define ANSI_FG_GREEN "\033[32m"
#define ANSI_FG_YELLOW "\033[33m"
#define ANSI_FG_BLUE "\033[34m"
#define ANSI_FG_MAGENTA "\033[35m"
#define ANSI_FG_CYAN "\033[36m"
#define ANSI_FG_WHITE "\033[37m"
#define ANSI_FG_BLACK_BRIGHT "\033[90m"
#define ANSI_FG_RED_BRIGHT "\033[91m"
#define ANSI_FG_GREEN_BRIGHT "\033[92m"
#define ANSI_FG_YELLOW_BRIGHT "\033[93m"
#define ANSI_FG_BLUE_BRIGHT "\033[94m"
#define ANSI_FG_MAGENTA_BRIGHT "\033[95m"
#define ANSI_FG_CYAN_BRIGHT "\033[96m"
#define ANSI_FG_WHITE_BRIGHT "\033[97m"
#define ANSI_BG_BLACK "\033[40m"
#define ANSI_BG_RED "\033[41m"
#define ANSI_BG_GREEN "\033[42m"
#define ANSI_BG_YELLOW "\033[43m"
#define ANSI_BG_BLUE "\033[44m"
#define ANSI_BG_MAGENTA "\033[45m"
#define ANSI_BG_CYAN "\033[46m"
#define ANSI_BG_WHITE "\033[47m"
#define ANSI_BG_BLACK_BRIGHT "\033[100m"
#define ANSI_BG_RED_BRIGHT "\033[101m"
#define ANSI_BG_GREEN_BRIGHT "\033[102m"
#define ANSI_BG_YELLOW_BRIGHT "\033[103m"
#define ANSI_BG_BLUE_BRIGHT "\033[104m"
#define ANSI_BG_MAGENTA_BRIGHT "\033[105m"
#define ANSI_BG_CYAN_BRIGHT "\033[106m"
#define ANSI_BG_WHITE_BRIGHT "\033[107m"
#define ANSI_RESET_ALL "\033[0m"
#define ANSI_RESET_FG "\033[39m"
#define ANSI_RESET_BG "\033[49m"
#define ANSI_RESET_EF_BOLD "\033[22m"
#define ANSI_RESET_EF_DIM "\033[22m"
#define ANSI_RESET_EF_ITALIC "\033[23m"
#define ANSI_RESET_EF_UNDERLINE "\033[24m"
#define ANSI_RESET_EF_BLINK "\033[25m"
#define ANSI_RESET_EF_REVERSE "\033[27m"
#define ANSI_RESET_EF_HIDDEN "\033[28m"
#define ANSI_RESET_EF_STRIKETHROUGH "\033[29m"
#define ANSI_RESET_EF_UNDERLINE_DOUBLE "\033[24m"
#define ANSI_ERASE_ALL "\033[2J"
#define ANSI_ERASE_LINE_RIGHT "\033[K"
#define ANSI_ERASE_LINE_LEFT "\033[1K"
#define ANSI_ERASE_LINE "\033[2K"
#define ANSI_CURSOR_HOME "\033[H"
#define ANSI_CURSOR_RIGHT "\033[1C"
#define ANSI_CURSOR_LEFT "\033[1D"
#define ANSI_CURSOR_UP "\033[1A"
#define ANSI_CURSOR_DOWN "\033[1B"
#define ANSI_CURSOR_LINE_NEXT "\033[E"
#define ANSI_CURSOR_LINE_PREV "\033[F"
#define ANSI_CURSOR_LINE_BEGIN "\033[1G"
#define ANSI_CURSOR_LINE_END "\033[999G"
#define ANSI_CURSOR_SAVE "\033[s"
#define ANSI_CURSOR_RESTORE "\033[u"
#define ANSI_CURSOR_HIDE "\033[?25l"
#define ANSI_CURSOR_SHOW "\033[?25h"

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
			util::io::raw_lock rawLock;
			util::io::nonblock_lock nonblockLock;
			std::this_thread::sleep_for(timeout);
			char input = defaultChar;
			while (read(STDIN_FILENO, &input, 1) == 1);
			return input;
		}

		int get_win_size (int &rows, int &cols);

		int get_cursor_pos (int &row, int &col);
	}
}