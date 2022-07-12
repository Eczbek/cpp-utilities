#include <iostream>
#include <limits>
#include <sys/ioctl.h>
#include <util/io>


util::io::Raw::Raw(const bool echo) noexcept {
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

util::io::NonBlock::NonBlock() noexcept {
	fcntl(STDIN_FILENO, F_SETFL, blocking | O_NONBLOCK);
}

util::io::NonBlock::~NonBlock() {
	fcntl(STDIN_FILENO, F_SETFL, blocking);
}

void util::io::ignore(const char until) noexcept {
	util::io::NonBlock nonblockLock;
	char input;
	while (input != until && read(STDIN_FILENO, &input, 1) == 1);
}

void util::io::ignore(std::streamsize characters) noexcept {
	util::io::NonBlock nonblockLock;
	char input;
	while (characters-- > 0 && read(STDIN_FILENO, &input, 1) == 1);
}

char util::io::waitChar(const bool echo) noexcept {
	util::io::Raw rawLock(echo);
	char input;
	read(STDIN_FILENO, &input, 1);
	return input;
}

char util::io::readChar(const char defaultChar) noexcept {
	util::io::Raw rawLock;
	util::io::NonBlock nonblockLock;
	char input = defaultChar;
	read(STDIN_FILENO, &input, 1);
	return input;
}

std::string util::io::readString() noexcept {
	util::io::Raw rawLock;
	util::io::NonBlock nonblockLock;
	std::string result;
	char input;
	while (read(STDIN_FILENO, &input, 1) == 1)
		result += input;
	return result;
}

void util::io::eraseAll() noexcept {
	std::cout << "\033[2J\033[H";
}

void util::io::eraseLine() noexcept {
	std::cout << "\033[2K\r";
}

util::io::Position util::io::getWindowSize() noexcept {
	winsize size;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
	return { size.ws_col, size.ws_row };
}

util::io::Position util::io::cursor::getPos() noexcept {
	util::io::Raw rawLock;
	write(STDOUT_FILENO, "\033[6n", 4);
	std::string buffer;
	char input;
	while (read(STDIN_FILENO, &input, 1) == 1 && input != 'R')
		buffer += input;
	util::io::Position position;
	sscanf(&buffer[0], "\033[%d;%d", &position.row, &position.column);
	return { position.row - 1, position.column - 1 };
}

void util::io::cursor::setPos(const util::io::Position position) noexcept {
	std::cout << "\033[" << (position.row + 1) << ';' << (position.column + 1) << 'H';
}

void util::io::cursor::move(const char direction, const int count) noexcept {
	std::cout << "\033[" << count << direction;
}

void util::io::cursor::hide() noexcept {
	std::cout << "\033[?25l";
}

void util::io::cursor::show() noexcept {
	std::cout << "\033[?25h";
}

void util::io::setStyle(const util::io::Style style) noexcept {
	std::cout << "\033[" << static_cast<int>(style) << 'm';
}
