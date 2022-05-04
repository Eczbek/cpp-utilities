#include "./console.hpp"

#include <limits>

void utility::console::ignoreLine (char until) {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), until);
}

void utility::console::clearScreen () {
	std::cout << "\033[2J\033[1;1H";
}

char utility::console::waitChar (bool echo) {
	struct termios cooked, raw;
	tcgetattr(STDIN_FILENO, &cooked);
	raw = cooked;
	raw.c_lflag &= ~ICANON;
	raw.c_lflag &= echo ? ECHO : ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
	const char input = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &cooked);
	return input;
}

char utility::console::readChar (bool echo) {
	struct termios cooked, raw;
	tcgetattr(STDIN_FILENO, &cooked);
	raw = cooked;
	raw.c_lflag &= ~ICANON;
	raw.c_lflag &= echo ? ECHO : ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
	fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
	char input = 0;
	read(STDIN_FILENO, &input, 1);
	tcsetattr(STDIN_FILENO, TCSANOW, &cooked);
	return input;
}
