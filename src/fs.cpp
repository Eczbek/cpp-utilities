#include <util/fs.hpp>


std::string util::fs::read(const std::string& path) noexcept {
	std::ifstream reader(path);
	return std::string(std::istreambuf_iterator<char>(reader), {});
}
