#ifndef UTIL_ALGORITHM_H
#define UTIL_ALGORITHM_H

#include <vector>

namespace util {
	namespace algorithm {
		template <typename T, class C>
		int binarySearch (const std::vector<T>& sortedVector, const C& searchCallback) {
			int left = 0;
			int right = sortedVector.size();
			while (true) {
				int middle = (right - left) / 2 + left;
				int check = searchCallback(sortedVector[middle]);
				if (!check)
					return middle;
				if (right - left < 2)
					return -1;
				if (check < 0)
					left = middle + 1;
				else
					right = middle;
			}
		}

		template <typename T, class C>
		std::vector<T> mergeSort (const std::vector<T>& vector, const C& sortCallback) {
			std::vector<T> result = vector;
			int size = result.size();
			if (size < 2)
				return result;
			int middle = size / 2;
			std::vector<T> left = mergeSort(std::vector<T>(result.begin(), result.begin() + middle), sortCallback);
			std::vector<T> right = mergeSort(std::vector<T>(result.begin() + middle, result.end()), sortCallback);
			result.clear();
			while (left.size() && right.size())
				if (sortCallback(left[0], right[0]) < 0) {
					result.push_back(left[0]);
					left.erase(left.begin());
				} else {
					result.push_back(right[0]);
					right.erase(right.begin());
				}
			result.insert(result.end(), left.begin(), left.end());
			result.insert(result.end(), right.begin(), right.end());
			return result;
		}
	}
}

#endif