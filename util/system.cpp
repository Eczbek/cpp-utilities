
#include "./system.h"

std::string util::system::name () {
#ifdef _WIN32
	return "Windows 32-bit";
#elif _WIN64
	return "Windows 64-bit";
#elif __APPLE__ || __MACH__
	return "Mac OS X";
#elif __linux__
	return "Linux";
#elif __unix || __unix__
	return "Unix";
#endif
	return "Other";
}
