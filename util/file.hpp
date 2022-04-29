#ifndef UTIL_FILE_H
#define UTIL_FILE_H

#include <string>

namespace util {
	namespace file {
		std::string read (const std::string& path);

		void write (const std::string& path, const std::string& data);
	}
}

#endif