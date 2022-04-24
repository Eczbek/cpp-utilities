#ifndef UTIL_ALGORITHM_H
#define UTIL_ALGORITHM_H

#include "./vector.h"

namespace util {
	namespace algorithm {
		template <typename T, class C>
		int binarySearch (const std::vector<T>& sortedVector, const C& searchCallback) {
			int left = 0;
			int right = sortedVector.size();
			while (true) {
				int middle = (right - left) / 2 + left;
				int check = searchCallback(sortedVector[middle]);
				if (!check) return middle;
				if (right - left < 2) return -1;
				if (check < 0) left = middle + 1;
				else right = middle;
			}
		}
	}
}

#endif