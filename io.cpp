#include "./io.hpp"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <cstring>

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

util::io::cursor::pos util::io::cursor::get () {
	util::io::raw_lock rawLock;
	write(STDOUT_FILENO, "\033[6n", 4);
	util::io::cursor::pos position;
	char buffer[32];
	for (int i = 0; i < 32; ++i) {
		read(STDIN_FILENO, &buffer[i], 1);
		if (buffer[i] == 'R')
			break;
	}
	sscanf(buffer, "\033[%d;%dR", &position.row, &position.col);
	return position;
}

util::io::cursor::pos util::io::cursor::get_max () {
	winsize size;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
	return { size.ws_row, size.ws_col };
}

void util::io::cursor::set (const util::io::cursor::pos position) {
	util::io::raw_lock rawLock;
	char buffer[32];
	sprintf(buffer, "\033[%d;%dH", position.row, position.col);
	write(STDOUT_FILENO, buffer, strlen(buffer));
}
