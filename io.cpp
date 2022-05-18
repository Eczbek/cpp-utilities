#include "./io.hpp"
#include <fcntl.h>
#include <sys/ioctl.h>

util::io::raw_lock::raw_lock () {
	tcgetattr(STDIN_FILENO, &cooked);
	termios raw = cooked;
	cfmakeraw(&raw);
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
	char input;
	util::io::nonblock_lock nonblockLock;
	while (input != until && read(STDIN_FILENO, &input, 1) == 1);
}

char util::io::char_wait () {
	util::io::raw_lock rawLock;
	return getchar();
}

char util::io::char_read (const char defaultChar) {
	char input = defaultChar;
	util::io::raw_lock rawLock;
	util::io::nonblock_lock nonblockLock;
	read(STDIN_FILENO, &input, 1);
	return input;
}

std::string util::io::string_read () {
	std::string result;
	char input;
	util::io::raw_lock rawLock;
	util::io::nonblock_lock nonblockLock;
	while (read(STDIN_FILENO, &input, 1) == 1)
		result += input;
	return result;
}

util::io::cursor::pos util::io::cursor::get_pos () {
	util::io::raw_lock rawLock;
	write(STDOUT_FILENO, "\033[6n", 4);
	std::string buffer;
	char input;
	while (read(STDIN_FILENO, &input, 1) == 1 && input != 'R')
		buffer += input;
	util::io::cursor::pos position;
	sscanf(&buffer[0], "\033[%d;%dR", &position.row, &position.col);
	return position;
}

util::io::cursor::pos util::io::cursor::get_max_pos () {
	winsize size;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
	return { size.ws_row, size.ws_col };
}

void util::io::cursor::set_pos (const util::io::cursor::pos position) {
	const std::string command = "\033[" + std::to_string(position.row) + ";" + std::to_string(position.col) + "H";
	util::io::raw_lock rawLock;
	write(STDOUT_FILENO, command.c_str(), command.size());
}
