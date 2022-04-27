
#include "./console.h"
#include <limits>

void util::console::ignoreLine (char until) {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), until);
}

void util::console::clearScreen () {
	std::cout << "\033[2J\033[1;1H";
}
