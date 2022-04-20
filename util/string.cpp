
#include "./string.h"


std::vector<std::string> util::string::split (std::string string, std::string delimiter) {
	std::vector<std::string> strings;
	int stringLength = string.length();
	int delimiterLength = delimiter.length();
	for (int i = stringLength > 1; i < stringLength; ++i) {
		if (string.substr(i, delimiterLength) == delimiter) {
			strings.push_back(string.substr(0, i));
			string = string.substr(i + delimiterLength);
			i = -!!delimiterLength;
		}
	}
	strings.push_back(string);
	return strings;
}

std::string util::string::join (std::vector<std::string> strings, std::string delimiter) {
	if (!strings.size()) {
		return "";
	}
	std::string string = strings[0];
	for (int i = 1; i < strings.size(); ++i) {
		string += delimiter + strings[i];
	}
	return string;
}
