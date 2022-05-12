#include "./io.hpp"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string>

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
	util::io::nonblock_lock nonblockLock;
	char temp;
	while (temp != until && read(STDIN_FILENO, &temp, 1) == 1);
}

char util::io::char_wait () {
	util::io::raw_lock rawLock;
	return getchar();
}

char util::io::char_read (const char defaultChar) {
	util::io::raw_lock rawLock;
	util::io::nonblock_lock nonblockLock;
	char input = defaultChar;
	read(STDIN_FILENO, &input, 1);
	return input;
}

int util::io::get_win_size (int &rows, int &cols) {
	winsize ws;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
		return -1;
	rows = ws.ws_row;
	cols = ws.ws_col;
	return 0;
}

int util::io::get_cursor_pos (int &row, int &col) {
	util::io::raw_lock rawLock;
	if (write(STDOUT_FILENO, "\033[6n", 4) != 4)
		return -1;
	char input;
	std::string buffer;
	while (read(STDIN_FILENO, &input, 1) == 1 && input != 'R')
		buffer += input;
	if (sscanf(&buffer[0], "\033[%d;%dR", &row, &col) != 2)
		return -1;
	return 0;
}
