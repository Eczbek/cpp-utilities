
#include "./string.hpp"

std::vector<std::string> util::string::split (std::string string, const std::string& delimiter) {
	std::vector<std::string> strings;
	int stringLength = string.length();
	int delimiterLength = delimiter.length();
	for (int i = stringLength > 1; i < stringLength; ++i)
		if (string.substr(i, delimiterLength) == delimiter) {
			strings.push_back(string.substr(0, i));
			string = string.substr(i + delimiterLength);
			i = -!!delimiterLength;
		}
	strings.push_back(string);
	return strings;
}

std::vector<std::string> util::string::split (std::string string, char delimiter) {
	std::vector<std::string> strings;
	int stringLength = string.length();
	for (int i = stringLength > 1; i < stringLength; ++i)
		if (string[i] == delimiter) {
			strings.push_back(string.substr(0, i));
			string = string.substr(i + 1);
			i = -1;
		}
	strings.push_back(string);
	return strings;
}
