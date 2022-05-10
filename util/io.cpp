#include "./io.hpp"
#include <fcntl.h>
#include <iostream>

// HERE BE DRAGONS

util::io::raw::raw (const bool echo) {
	tcgetattr(STDIN_FILENO, &cooked);
	termios raw = cooked;
	raw.c_lflag &= ~ICANON;
	raw.c_lflag &= echo ? ECHO : ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

util::io::raw::~raw () {
	tcsetattr(STDIN_FILENO, TCSANOW, &cooked);
}

util::io::nonblock::nonblock () {
	fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
}

util::io::nonblock::~nonblock () {
	fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) & ~O_NONBLOCK);
}

void util::io::ignore (const char until) {
	util::io::nonblock lock();
	char temp;
	while (temp != until && read(STDIN_FILENO, &temp, 1) == 1);
}

void util::io::clear_screen () {
	std::cout << "\033[2J\033[1;1H";
}

char util::io::char_wait (const bool echo) {
	util::io::raw lock(echo);
	return getchar();
}

char util::io::char_read (const bool echo, const char defaultChar) {
	util::io::raw lock1(echo);
	util::io::nonblock lock2();
	char input = defaultChar;
	read(STDIN_FILENO, &input, 1);
	return input;
}