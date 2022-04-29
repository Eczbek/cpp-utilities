#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include <vector>
#include <string>

namespace util {
	namespace string {
		std::vector<std::string> split (std::string string, const std::string& delimiter);

		std::vector<std::string> split (std::string string, char delimiter);
	}
}

#endif