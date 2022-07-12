#include <util/map>
#include <util/str>
#include <array>
#include <limits>


std::vector<std::string> util::str::split(const std::string& string, std::string_view delimiter) noexcept {
	std::vector<std::string> segments;
	std::size_t i = 0;
	for (std::size_t j = 0; j < string.size() - i; ++j)
		if (string.substr(j, delimiter.size()) == delimiter) {
			segments.push_back(string.substr(i, j - i));
			i = j += delimiter.size();
		}
	segments.push_back(string.substr(i));
	return segments;
}

std::vector<std::string> util::str::split(const std::string& string, const char delimiter) noexcept {
	std::vector<std::string> segments;
	std::size_t i = 0;
	for (std::size_t j = 0; j < string.size(); ++j)
		if (string[j] == delimiter) {
			segments.push_back(string.substr(i, j - i));
			i = ++j;
		} 
	segments.push_back(string.substr(i));
	return segments;
}

std::string util::str::trunc(const std::string& string, const std::size_t length, const std::string& suffix) noexcept {
	return string.size() > length		
		? string.substr(0, length - suffix.size()) + suffix
		: string;
}

std::string util::str::trimLeft(const std::string& string, const char character) noexcept {
	for (std::size_t i = 0; i < string.size(); ++i)
		if (string[i] != character)
			return string.substr(i);
	return "";
}

std::string util::str::trimRight(const std::string& string, const char character) noexcept {
	for (std::size_t i = string.size(); i > 0; --i)
		if (string[i - 1] != character)
			return string.substr(0, i);
	return "";
}

std::string util::str::trimLeft(const std::string& string, std::string_view characters) noexcept {
	util::OrderedMap<char, bool> charMap;
	for (const char character: characters)
		charMap[character] = true;
	for (std::size_t i = 0; i < string.size(); ++i)
		if (!charMap[string[i]])
			return string.substr(i);
	return "";
}

std::string util::str::trimRight(const std::string& string, std::string_view characters) noexcept {
	util::OrderedMap<char, bool> charMap;
	for (const char character: characters)
		charMap[character] = true;
	for (std::size_t i = string.size(); i > 0; --i)
		if (!charMap[string[i - 1]])
			return string.substr(0, i);
	return "";
}
