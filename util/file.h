#ifndef UTIL_FILE_H
#define UTIL_FILE_H

#include <string>

namespace util {
	namespace file {
		std::string read (std::string path);

		void write (std::string path, std::string data);
	}
}

#endif