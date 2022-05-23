#pragma once

#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WINDOWS__)
#	define OS_WINDOWS true
#elif defined(__APPLE__) || defined(__MACH__)
#	define OS_MAC true
#elif defined(__unix__) || defined(__unix) || defined(unix)
#	define OS_UNIX true
#endif
