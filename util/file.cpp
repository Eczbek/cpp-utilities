
#include "./file.h"
#include <fstream>


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
