
#include "./file.h"
#include <fstream>

std::string util::file::read (std::string path) {
	std::ifstream reader(path);
	return std::string(std::istreambuf_iterator<char>(reader), {});
}

void util::file::write (std::string path, std::string data) {
	std::ofstream writer(path);
	if (writer) {
		writer << data;
	}
}
