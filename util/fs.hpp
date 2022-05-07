#pragma once

#include <string>
#include <string_view>
#include <fstream>

namespace util {
	namespace fs {
		std::string read (const std::string& path);
		
		template <typename DataType = std::string_view>
		void write (const std::string& path, const DataType& data) {
			std::ofstream writer(path);
			if (writer)
				writer << data;
		}
	}
}
