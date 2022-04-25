#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include <vector>
#include <string>

namespace util {
	namespace string {
		std::vector<std::string> split (std::string string, const std::string& delimiter = "");

		std::string join (const std::vector<std::string>& strings, const std::string& delimiter = ", ");
	}
}

#endif