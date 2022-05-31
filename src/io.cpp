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
	fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
}

util::io::nonblock::~nonblock() {
	fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) & ~O_NONBLOCK);
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

char util::io::char_wait() {
	util::io::raw rawLock;
	char input;
	read(STDIN_FILENO, &input, 1);
	return input;
}

char util::io::char_read(const char defaultChar) {
	util::io::raw rawLock;
	util::io::nonblock nonblockLock;
	char input = defaultChar;
	read(STDIN_FILENO, &input, 1);
	return input;
}

std::string util::io::string_read() {
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

void util::io::get_win_size(int& rows, int& cols) {
	winsize size;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
	rows = size.ws_row;
	cols = size.ws_col;
}

void util::io::cursor::get(int& row, int& col) {
	util::io::raw rawLock;
	write(STDOUT_FILENO, "\033[6n", 4);
	std::string buffer;
	char input;
	while (read(STDIN_FILENO, &input, 1) == 1 && input != 'R')
		buffer += input;
	sscanf(&buffer[0], "\033[%d;%d", &row, &col);
}

void util::io::cursor::set(const int row, const int col) {
	std::cout << "\033[" << row << ';' << col << 'H';
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