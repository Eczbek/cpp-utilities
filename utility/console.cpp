
#include "./console.hpp"
#include <limits>
#include <termios.h>
#include <unistd.h>

void utility::console::ignoreLine (char until) {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), until);
}

char utility::console::getCharUnix (bool echo) {
	static struct termios termiosCooked, termiosRaw;
	tcgetattr(STDIN_FILENO, &termiosCooked);
	termiosRaw = termiosCooked;
	termiosRaw.c_lflag &= ~(ICANON | (echo ? 0 : ECHO));

	tcsetattr(STDIN_FILENO, TCSANOW, &termiosRaw);
	const char result = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &termiosCooked);
	return result;
}

void utility::console::clearScreen () {
	std::cout << "\033[2J\033[1;1H";
}
