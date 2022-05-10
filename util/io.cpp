#include "./io.hpp"
#include <fcntl.h>
#include <iostream>

// HERE BE DRAGONS

util::io::raw_lock::raw_lock (const bool echo) {
	tcgetattr(STDIN_FILENO, &cooked);
	termios raw = cooked;
	raw.c_lflag &= ~ICANON;
	raw.c_lflag &= echo ? ECHO : ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

util::io::raw_lock::~raw_lock () {
	tcsetattr(STDIN_FILENO, TCSANOW, &cooked);
}

util::io::nonblock_lock::nonblock_lock () {
	fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
}

util::io::nonblock_lock::~nonblock_lock () {
	fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) & ~O_NONBLOCK);
}

void util::io::ignore (const char until) {
	util::io::nonblock_lock nonblockLock;
	char temp;
	while (temp != until && read(STDIN_FILENO, &temp, 1) == 1);
}

void util::io::clear_screen () {
	std::cout << "\033[2J\033[1;1H";
}

char util::io::char_wait (const bool echo) {
	util::io::raw_lock rawLock(echo);
	return getchar();
}

char util::io::char_read (const bool echo, const char defaultChar) {
	util::io::raw_lock rawLock(echo);
	util::io::nonblock_lock nonblockLock;
	char input = defaultChar;
	read(STDIN_FILENO, &input, 1);
	return input;
}