
#include "./string.hpp"

std::vector<std::string_view> utility::string::split (std::string_view string, const std::string_view& delimiter) {
	std::vector<std::string_view> strings;
	const int delimiterLength = delimiter.length();
	for (int i = string.length() > 1; i < string.length(); ++i)
		if (string.substr(i, delimiterLength) == delimiter) {
			strings.push_back(string.substr(0, i));
			string = string.substr(i + delimiterLength);
			i = -!!delimiterLength;
		}
	strings.push_back(string);
	return strings;
}

std::vector<std::string_view> utility::string::split (std::string_view string, char delimiter) {
	std::vector<std::string_view> strings;
	for (int i = string.length() > 1; i < string.length(); ++i)
		if (string[i] == delimiter) {
			strings.push_back(string.substr(0, i));
			string = string.substr(i + 1);
			i = -1;
		}
	strings.push_back(string);
	return strings;
}
