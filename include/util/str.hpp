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

		std::string trimLeft(const std::string& string, const char character);

		std::string trimRight(const std::string& string, const char character);

		std::string trimLeft(const std::string& string, const std::string_view& characters);

		std::string trimRight(const std::string& string, const std::string_view& characters);
	}
}
