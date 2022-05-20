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

		std::string string_read (const int chunkSize = 1);

		void erase_all ();

		void erase_line ();

		void reset_style ();

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