#include <util/fs>


std::string util::fs::read(const std::string& path) {
	std::ifstream reader(path);
	return std::string(std::istreambuf_iterator<char>(reader), {});
}
