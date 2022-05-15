#pragma once
#include <string>
#include <vector>
#include <string_view>

namespace util {
	namespace str {
		std::vector<std::string> split (const std::string& string, const std::string_view& delimiter);

		std::vector<std::string> split (const std::string& string, const char delimiter);
	}
}