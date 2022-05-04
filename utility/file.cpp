
#include "./file.hpp"

std::string utility::file::read (const std::string& path) {
	std::ifstream reader(path);
	return std::string(std::istreambuf_iterator<char>(reader), {});
}
