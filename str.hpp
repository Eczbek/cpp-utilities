#pragma once

#include <string>
#include <string_view>
#include <vector>


namespace util {
	namespace str {
		std::vector<std::string> split(const std::string& string, const std::string_view& delimiter);

		std::vector<std::string> split(const std::string& string, const char delimiter);

		std::string truncate(const std::string& string, const std::size_t length, const std::string& suffix = "...");

		std::string trim_left(const std::string& string, const char character);

		std::string trim_right(const std::string& string, const char character);

		std::string trim_left(const std::string& string, const std::string_view& characters);

		std::string trim_right(const std::string& string, const std::string_view& characters);
	}
}