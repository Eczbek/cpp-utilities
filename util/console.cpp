
#include "./console.h"
#include <limits>

void util::console::ignoreLine (char until) {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), until);
}
