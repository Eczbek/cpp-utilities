#ifndef UTILITY_FILE_HPP
#define UTILITY_FILE_HPP

#include <string>
#include <string_view>
#include <fstream>

namespace utility {
	namespace file {
		std::string read (const std::string& path);
		
		template <typename DataType = std::string_view>
		void write (const std::string& path, const DataType& data) {
			std::ofstream writer(path);
			if (writer)
				writer << data;
		}
	}
}

#endif