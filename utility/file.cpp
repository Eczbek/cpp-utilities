
#include "./file.hpp"
#include <fstream>

std::string utility::file::read (const std::string& path) {
	std::ifstream reader(path);
	return std::string(std::istreambuf_iterator<char>(reader), {});
}

void utility::file::write (const std::string& path, const std::string_view& data) {
	std::ofstream writer(path);
	if (writer)
		writer << data;
}
