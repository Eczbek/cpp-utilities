#include "./io.hpp"

#include <fcntl.h>
#include <iostream>

util::io::raw::raw () {
	tcgetattr(STDIN_FILENO, &cooked);
	termios raw = cooked;
	cfmakeraw(&raw);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

util::io::raw::~raw () {
	tcsetattr(STDIN_FILENO, TCSANOW, &cooked);
}

void util::io::nonblock () {
	fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
}

void util::io::ignr () {
	util::io::nonblock();
	char temp;
	while (read(STDIN_FILENO, &temp, 1) == 1);
}

void util::io::clr_scrn () {
	std::cout << "\033[2J\033[1;1H";
}

char util::io::char_wait () {
	util::io::raw();
	return getchar();
}

char util::io::char_read () {
	util::io::raw();
	util::io::nonblock();
	char input = 0;
	read(STDIN_FILENO, &input, 1);
	return input;
}