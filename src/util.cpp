
#include "./util.h"
#include <random>
#include <limits>
#include <fstream>


void util::console::ignoreLine () {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string util::file::read (std::string path) {
	std::ifstream reader(path);
	std::string result;
	if (reader.is_open()) {
		std::string line;
		while (reader.good()) {
			std::getline(reader, line);
			result += '\n' + line;
		}
	}
	return result.substr(1);
}

void util::file::write (std::string path, std::string content) {
	std::ofstream writer(path);
	if (writer.is_open()) {
		writer << content;
	}
}

double util::random::get (double max, double min, bool inclusive) {
	static std::mt19937 rng32 (std::random_device {}());
	return rng32() / 2.0 / INT32_MAX * (max - min + inclusive) + min;
}

std::vector<std::string> util::string::split (std::string string, std::string delimiter) {
	std::vector<std::string> strings;
	for (int i = string.length() > 1; i < string.length(); ++i) {
		if (string.substr(i, delimiter.length()) == delimiter) {
			strings.push_back(string.substr(0, i));
			string = string.substr(i + delimiter.length());
			i = 0 - !!delimiter.length();	
		}
	}
	strings.push_back(string);
	return strings;
}

std::string util::string::join (std::vector<std::string> strings, std::string delimiter) {
	std::string string = strings[0];
	for (int i = 1; i < strings.size(); ++i) {
		string += delimiter + strings[i];
	}
	return string;
}
