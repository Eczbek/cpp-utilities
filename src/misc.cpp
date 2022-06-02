#include <cmath>
#include <util/misc.hpp>


util::display::display(const int width, const int height, const char fill, const std::string& padX, const std::string& padY)
	: width(width), height(height), padX(padX.length() + 1), padY(padY.length())
{
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x)
			value += fill + padX;
		value += padY;
	}
}

char& util::display::operator[](const util::io::pos position) {
	return value[value.length() - (position.row + 1) * width * padX - position.row * padY + (position.col - 1) * padX + std::ceil(padX / 2.0)];
}
