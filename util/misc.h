#ifndef UTIL_MISC_H
#define UTIL_MISC_H

#include <string>
#include <cstdarg>

namespace util {
	namespace misc {
		template <typename T>
		std::string getType (const T& value) {
			return std::string(typeid(value).name()).substr(1);
		}
	}
}

#endif