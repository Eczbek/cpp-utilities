#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include <vector>
#include <string>


namespace util {
	namespace string {
		std::vector<std::string> split (std::string string, std::string delimiter = "");

		std::vector<std::string> split (std::string string, char delimiter);

		std::string join (std::vector<std::string> strings, std::string delimiter = ", ");
	}
}

#endif