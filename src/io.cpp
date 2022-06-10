#include <util/io.hpp>
#include <fcntl.h>
#include <iostream>
#include <sys/ioctl.h>


util::io::raw::raw() {
	tcgetattr(STDIN_FILENO, &cooked);
	termios raw = cooked;
	cfmakeraw(&raw);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

util::io::raw::~raw() {
	tcsetattr(STDIN_FILENO, TCSANOW, &cooked);
}

util::io::nonblock::nonblock() {
	fcntl(STDIN_FILENO, F_SETFL, blocking | O_NONBLOCK);
}

util::io::nonblock::~nonblock() {
	fcntl(STDIN_FILENO, F_SETFL, blocking);
}

void util::io::ignore(const char until) {
	util::io::nonblock nonblockLock;
	char input;
	while (input != until && read(STDIN_FILENO, &input, 1) == 1);
}

void util::io::ignore(std::streamsize characters) {
	util::io::nonblock nonblockLock;
	char input;
	while (characters-- > 0 && read(STDIN_FILENO, &input, 1) == 1);
}

char util::io::wait_char() {
	util::io::raw rawLock;
	char input;
	read(STDIN_FILENO, &input, 1);
	return input;
}

char util::io::read_char(const char defaultChar) {
	util::io::raw rawLock;
	util::io::nonblock nonblockLock;
	char input = defaultChar;
	read(STDIN_FILENO, &input, 1);
	return input;
}

std::string util::io::read_string() {
	util::io::raw rawLock;
	util::io::nonblock nonblockLock;
	std::string result;
	char input;
	while (read(STDIN_FILENO, &input, 1) == 1)
		result += input;
	return result;
}

void util::io::erase_all() {
	std::cout << "\033[2J";
}

void util::io::erase_line() {
	std::cout << "\033[2K";
}

util::io::pos util::io::get_win_size() {
	winsize size;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
	return { size.ws_col, size.ws_row };
}

util::io::pos util::io::cursor::get() {
	util::io::raw rawLock;
	write(STDOUT_FILENO, "\033[6n", 4);
	std::string buffer;
	char input;
	while (read(STDIN_FILENO, &input, 1) == 1 && input != 'R')
		buffer += input;
	util::io::pos position;
	sscanf(&buffer[0], "\033[%d;%d", &position.row, &position.col);
	return position;
}

void util::io::cursor::set(const util::io::pos position) {
	std::cout << "\033[" << position.row << ';' << position.col << 'H';
}

void util::io::cursor::move(const char direction, const int count) {
	std::cout << "\033[" << count << direction;
}

void util::io::cursor::hide() {
	std::cout << "\033[?25l";
}

void util::io::cursor::show() {
	std::cout << "\033[?25h";
}

util::io::style::style(const int style) {
	std::cout << "\033[" << style << "m";
}

util::io::style::~style() {
	std::cout << "\033[" << util::io::style::NONE << "m";
}
