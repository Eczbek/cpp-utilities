#ifndef UTILITY_ALGORITHM_HPP
#define UTILITY_ALGORITHM_HPP

#include <vector>

namespace utility {
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
			int middle = vector.size() / 2;
			if (!middle)
				return vector;
			std::vector<T> left = mergeSort(std::vector<T>(vector.begin(), vector.begin() + middle), sortCallback);
			std::vector<T> right = mergeSort(std::vector<T>(vector.begin() + middle, vector.end()), sortCallback);
			std::vector<T> result;
			while (left.size() && right.size())
				if (sortCallback(right[0], left[0])) {
					result.push_back(right[0]);
					right.erase(right.begin());
				} else {
					result.push_back(left[0]);
					left.erase(left.begin());
				}
			result.insert(result.end(), left.begin(), left.end());
			result.insert(result.end(), right.begin(), right.end());
			return result;
		}
	}
}

#endif