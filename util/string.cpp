
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

std::string util::string::join (const std::vector<std::string>& strings, const std::string& delimiter) {
	if (!strings.size())
		return "";
	std::string string = strings[0];
	for (int i = 1; i < strings.size(); ++i)
		string += delimiter + strings[i];
	return string;
}

std::string util::string::join (const std::vector<std::string>& strings, char delimiter) {
	return util::string::join(strings, std::string(1, delimiter));
}

std::string util::string::join (const std::vector<char>& characters, const std::string& delimiter) {
	if (!characters.size())
		return "";
	std::string string = std::string(1, characters[0]);
	for (int i = 1; i < characters.size(); ++i)
		string += delimiter + characters[i];
	return string;
}

std::string util::string::join (const std::vector<char>& characters, char delimiter) {
	return util::string::join(characters, std::string(1, delimiter));
}
