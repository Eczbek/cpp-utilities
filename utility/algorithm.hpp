#pragma once

#include "./random.hpp"
#include <vector>

namespace utility {
	namespace algorithm {
		template <typename VectorType, class LambdaType>
		int binarySearch (const std::vector<VectorType>& sortedVector, const LambdaType& searchCallback) {
			int left = 0;
			int right = sortedVector.size();
			while (true) {
				const int middle = (right - left) / 2 + left;
				const int check = searchCallback(sortedVector[middle]);
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

		template <typename VectorType, class LambdaType>
		std::vector<VectorType> mergeSort (const std::vector<VectorType>& vector, const LambdaType& sortCallback) {
			const int middle = vector.size() / 2;
			if (!middle)
				return vector;
			std::vector<VectorType> left = mergeSort(std::vector<VectorType>(vector.begin(), vector.begin() + middle), sortCallback);
			std::vector<VectorType> right = mergeSort(std::vector<VectorType>(vector.begin() + middle, vector.end()), sortCallback);
			std::vector<VectorType> sorted;
			while (left.size() && right.size())
				if (sortCallback(right[0], left[0])) {
					sorted.push_back(right[0]);
					right.erase(right.begin());
				} else {
					sorted.push_back(left[0]);
					left.erase(left.begin());
				}
			sorted.insert(sorted.end(), left.begin(), left.end());
			sorted.insert(sorted.end(), right.begin(), right.end());
			return result;
		}

		template <typename VectorType>
		std::vector<VectorType> shuffle (std::vector<VectorType> vector) {
			for (int i = vector.size() - 1; i > 0; --i) {
				const int j = utility::random::mt32(i);
				const VectorType temp = vector[i];
				vector[i] = vector[j];
				vector[j] = temp;
			}
			return vector;
		}
	}
}
