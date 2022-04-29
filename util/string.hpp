#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include <vector>
#include <string>

namespace util {
	namespace string {
		std::vector<std::string> split (std::string string, const std::string& delimiter);

		std::vector<std::string> split (std::string string, char delimiter);

		std::string join (const std::vector<std::string>& strings, const std::string& delimiter);

		std::string join (const std::vector<std::string>& strings, char delimiter);

		std::string join (const std::vector<char>& characters, const std::string& delimiter);

		std::string join (const std::vector<char>& characters, char delimiter);
	}
}

#endif