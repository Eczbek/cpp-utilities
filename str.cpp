#include "./str.hpp"

std::vector<std::string> util::str::split (const std::string& string, const std::string_view& delimiter) {
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

std::string util::str::truncate (const std::string& string, const std::size_t& length, const std::string& suffix) {
	return string.length() <= length
		? string
		: string.substr(0, length - suffix.length()) + suffix;
}
