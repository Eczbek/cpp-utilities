#pragma once

#include <util/io.hpp>


namespace util {
	struct display {
		std::string value;
		int width;
		int height;
		int padX;
		int padY;

		display(const int width, const int height, const char fill, const std::string& padX = " ", const std::string& padY = "\n");

		char& operator[](const util::io::pos position);
	};
}
