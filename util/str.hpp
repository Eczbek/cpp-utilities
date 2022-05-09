#pragma once
#include <string>
#include <vector>

namespace util {
	namespace str {
		std::vector<std::string> split (const std::string& string, const std::string& delimiter);

		std::vector<std::string> split (const std::string& string, const char delimiter);
	}
}