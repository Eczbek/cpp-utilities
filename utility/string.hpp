#ifndef UTILITY_STRING_HPP
#define UTILITY_STRING_HPP

#include <string_view>
#include <vector>

namespace utility {
	namespace string {
		template <typename StringType = std::string>
		std::vector<StringType> split (StringType string, const StringType& delimiter) {
			std::vector<StringType> segments;
			const int delimiterLength = delimiter.length();
			for (int i = string.length() > 1; i < string.length(); ++i)
				if (string.substr(i, delimiterLength) == delimiter) {
					segments.push_back(string.substr(0, i));
					string = string.substr(i + delimiterLength);
					i = -!!delimiterLength;
				}
			segments.push_back(string);
			return segments;
		}

		template <typename StringType = std::string>
		std::vector<StringType> split (StringType string, char delimiter) {
			std::vector<StringType> segments;
			for (int i = string.length() > 1; i < string.length(); ++i)
				if (string[i] == delimiter) {
					segments.push_back(string.substr(0, i));
					string = string.substr(i + 1);
					i = -1;
				}
			segments.push_back(string);
			return segments;
		}
	}
}

#endif