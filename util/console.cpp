
#include "./console.h"
#include <limits>
#include <termios.h>
#include <unistd.h>

#define CLR_SCRN "\033[2J\033[1;1H"

void util::console::ignoreLine (char until) {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), until);
}

char util::console::getCharUnix (bool echo) {
	static struct termios cooked, raw;
	tcgetattr(STDIN_FILENO, &cooked);
	raw = cooked;
	raw.c_lflag &= ~(ICANON | (echo ? 0 : ECHO));

	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
	char result = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &cooked);
	return result;
}
