#pragma once

#include <fcntl.h>
#include <string>
#include <termios.h>
#include <thread>
#include <unistd.h>


namespace util {
	namespace io {
		class Raw {
		private:
			termios cooked;

		public:
			Raw(const bool echo = false) noexcept;

			~Raw();
		};

		class NonBlock {
		private:
			const int blocking = fcntl(STDIN_FILENO, F_GETFL);

		public:
			NonBlock() noexcept;

			~NonBlock();
		};

		void ignore(const char until = 0) noexcept;

		void ignore(std::streamsize characters) noexcept;

		char waitChar(const bool echo = false) noexcept;

		char readChar(const char defaultChar = 0) noexcept;

		template <typename Duration>
		char timeoutChar(const Duration timeout, const char defaultChar = 0, const bool echo = false, const bool readAll = true) noexcept {
			util::io::Raw rawLock(echo);
			util::io::NonBlock nonblockLock;
			std::this_thread::sleep_for(timeout);
			char input = defaultChar;
			while (read(STDIN_FILENO, &input, 1) == 1 && readAll);
			return input;
		}

		std::string readString() noexcept;

		void eraseAll() noexcept;

		void eraseLine() noexcept;

		struct Position {
			int row;
			int col;
		};

		util::io::Position getWindowSize() noexcept;

		namespace cursor {
			enum: char {
				UP = 'A',
				DOWN,
				RIGHT,
				LEFT
			};

			util::io::Position getPos() noexcept;

			void setPos(const util::io::Position position) noexcept;

			void move(const char direction, const int count = 1) noexcept;

			void hide() noexcept;

			void show() noexcept;
		}

		enum class Style {
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

		void setStyle(const util::io::Style style) noexcept;
	}
}
