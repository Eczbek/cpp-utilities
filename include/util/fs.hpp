#pragma once

#include <fstream>
#include <string_view>


namespace util {
	namespace fs {
		std::string read(const std::string& path) noexcept;
		
		template <typename Data = std::string_view>
		void write(const std::string& path, const Data& data) noexcept {
			std::ofstream writer(path);
			if (writer)
				writer << data;
		}

		template <typename Data = std::string_view>
		void append(const std::string& path, const Data& data) noexcept {
			std::ofstream writer(path, std::ios_base::app);
			if (writer)
				writer << data;
		}
	}
}
