#include "./str.hpp"

std::vector<std::string> util::str::split (const std::string& string, const std::string& delimiter) {
	std::vector<std::string> segments;
	int i = 0;
	for (int j = 0; j < string.length() - i; ++j)
		if (string.substr(j, delimiter.length()) == delimiter) {
			segments.push_back(string.substr(i, j));
			i = j + delimiter.length();
			j = -1;
		}
	segments.push_back(string.substr(i));
	return segments;
}

std::vector<std::string> util::str::split (const std::string& string, const char delimiter) {
	std::vector<std::string> segments;
	int i = 0;
	for (int j = 0; j < string.length(); ++j)
		if (string[j] == delimiter) {
			segments.push_back(string.substr(i, j - i));
			i = ++j;
		}
	segments.push_back(string.substr(i));
	return segments;
}
