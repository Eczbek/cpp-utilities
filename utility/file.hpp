#ifndef UTILITY_FILE_HPP
#define UTILITY_FILE_HPP

#include <string>
#include <string_view>

namespace utility {
	namespace file {
		std::string read (const std::string& path);

		void write (const std::string& path, const std::string_view& data);
	}
}

#endif