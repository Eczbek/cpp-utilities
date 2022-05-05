#pragma once

#include <vector>
#include <random>

namespace utility {
	namespace algorithm {
		template <typename IteratorType, class LambdaType>
		int binarySearch (IteratorType begin, IteratorType end, const LambdaType& searchCallback) {
			const IteratorType start = begin;
			while (true) {
				const IteratorType middle = begin + (end - begin) / 2;
				const int check = searchCallback(*middle);
				if (!check)
					return std::distance(start, middle);
				if (end - begin < 2)
					return -1;
				if (check < 0)
					begin = middle + 1;
				else
					end = middle;
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
			return sorted;
		}

		template <typename VectorType>
		std::vector<VectorType> shuffle (std::vector<VectorType> vector) {
			std::mt19937 rng32 (std::random_device{}());
			for (int i = vector.size() - 1; i > 0; --i) {
				const int j = std::uniform_int_distribution<>(0, i)(rng32);
				const VectorType temp = vector[i];
				vector[i] = vector[j];
				vector[j] = temp;
			}
			return vector;
		}
	}
}
