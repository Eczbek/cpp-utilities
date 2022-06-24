#include <iostream>
#include <limits>
#include <sys/ioctl.h>
#include <util/io.hpp>


util::io::Raw::Raw(const bool echo) {
	tcgetattr(STDIN_FILENO, &cooked);
	termios raw = cooked;
	cfmakeraw(&raw);
	if (echo)
		raw.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

util::io::Raw::~Raw() {
	tcsetattr(STDIN_FILENO, TCSANOW, &cooked);
}

util::io::NonBlock::NonBlock() {
	fcntl(STDIN_FILENO, F_SETFL, blocking | O_NONBLOCK);
}

util::io::NonBlock::~NonBlock() {
	fcntl(STDIN_FILENO, F_SETFL, blocking);
}

void util::io::ignore(const char until) {
	util::io::NonBlock nonblockLock;
	char input;
	while (input != until && read(STDIN_FILENO, &input, 1) == 1);
}

void util::io::ignore(std::streamsize characters) {
	util::io::NonBlock nonblockLock;
	char input;
	while (characters-- > 0 && read(STDIN_FILENO, &input, 1) == 1);
}

char util::io::waitChar(const bool echo) {
	util::io::Raw rawLock(echo);
	char input;
	read(STDIN_FILENO, &input, 1);
	return input;
}

char util::io::readChar(const char defaultChar) {
	util::io::Raw rawLock;
	util::io::NonBlock nonblockLock;
	char input = defaultChar;
	read(STDIN_FILENO, &input, 1);
	return input;
}

std::string util::io::readString() {
	util::io::Raw rawLock;
	util::io::NonBlock nonblockLock;
	std::string result;
	char input;
	while (read(STDIN_FILENO, &input, 1) == 1)
		result += input;
	return result;
}

void util::io::eraseAll() {
	std::cout << "\033[2J\033[H";
}

void util::io::eraseLine() {
	std::cout << "\033[2K\033[0G";
}

util::io::Position util::io::getWindowSize() {
	winsize size;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
	return { size.ws_col, size.ws_row };
}

util::io::Position util::io::cursor::getPos() {
	util::io::Raw rawLock;
	write(STDOUT_FILENO, "\033[6n", 4);
	std::string buffer;
	char input;
	while (read(STDIN_FILENO, &input, 1) == 1 && input != 'R')
		buffer += input;
	util::io::Position position;
	sscanf(&buffer[0], "\033[%d;%d", &position.row, &position.col);
	return position;
}

void util::io::cursor::setPos(const util::io::Position position) {
	std::cout << "\033[" << (position.row + 1) << ';' << (position.col + 1) << 'H';
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

void util::io::setStyle(const util::io::Style style) {
	std::cout << "\033[" << static_cast<int>(style) << 'm';
}
