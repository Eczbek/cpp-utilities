#ifndef UTILITY_STRING_HPP
#define UTILITY_STRING_HPP

#include <string>
#include <string_view>
#include <vector>

namespace utility {
	namespace string {
		std::vector<std::string_view> split (std::string_view string, const std::string_view& delimiter);

		std::vector<std::string_view> split (std::string_view string, char delimiter);
	}
}

#endif