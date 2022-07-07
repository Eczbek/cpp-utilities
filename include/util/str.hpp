#pragma once

#include <array>
#include <limits>
#include <string>
#include <string_view>
#include <vector>


namespace util {
	namespace str {
		std::vector<std::string> split(const std::string& string, std::string_view delimiter) noexcept;

		std::vector<std::string> split(const std::string& string, const char delimiter) noexcept;

		std::string trunc(const std::string& string, const std::size_t length, const std::string& suffix = "...") noexcept;

		std::string trimLeft(const std::string& string, const char character) noexcept;

		std::string trimRight(const std::string& string, const char character) noexcept;

		std::string trimLeft(const std::string& string, std::string_view characters) noexcept;

		std::string trimRight(const std::string& string, std::string_view characters) noexcept;
	}
}
