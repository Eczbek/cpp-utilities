#pragma once

#include <array>
#include <limits>
#include <string>
#include <string_view>
#include <vector>


namespace util {
	namespace str {
		std::vector<std::string> split(const std::string& string, const std::string_view& delimiter);

		std::vector<std::string> split(const std::string& string, const char delimiter);

		std::string trunc(const std::string& string, const std::size_t length, const std::string& suffix = "...");

		std::string trim_left(const std::string& string, const char character);

		std::string trim_right(const std::string& string, const char character);

		std::string trim_left(const std::string& string, const std::string_view& characters);

		std::string trim_right(const std::string& string, const std::string_view& characters);

		template <typename Value = std::size_t>
		struct CharMap {
			std::array<Value, std::numeric_limits<char>::max() - std::numeric_limits<char>::min() + 1> characters;
			
			Value& operator[](const char character) {
				return characters[character - std::numeric_limits<char>::min()];
			}
		};
	}
}
