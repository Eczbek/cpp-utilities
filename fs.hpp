#pragma once
#include <string_view>
#include <fstream>

namespace util {
	namespace fs {
		std::string read (const std::string& path);
		
		template <typename Value = std::string_view>
		void write (const std::string& path, const Value& data) {
			std::ofstream writer(path);
			if (writer)
				writer << data;
		}

		template <typename Value = std::string_view>
		void append (const std::string& path, const Value& data) {
			std::ofstream writer(path, std::ios_base::app);
			if (writer)
				writer << data;
		}
	}
}
