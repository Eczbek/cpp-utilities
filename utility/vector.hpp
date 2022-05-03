#ifndef UTILITY_VECTOR_HPP
#define UTILITY_VECTOR_HPP

#include <vector>
#include <cmath>
#include <string_view>
#include <unordered_map>

namespace utility {
	namespace vector {
		template <typename VectorType>
		std::vector<std::vector<VectorType>> chunk (std::vector<VectorType> vector, int chunkSize, bool overflow = true) {
			std::vector<std::vector<VectorType>> result;
			while (true) {
				const int vectorSize = std::fmin(vector.size(), chunkSize);
				if (vectorSize < chunkSize && !overflow || !vectorSize)
					return result;
				result.push_back(std::vector<VectorType>(vector.begin(), vector.begin() + vectorSize));
				vector = std::vector<VectorType>(vector.begin() + vectorSize, vector.end());
			}
		}

		template <typename VectorType, class LambdaType>
		std::vector<std::vector<VectorType>> chunk (std::vector<VectorType> vector, const LambdaType& chunkCallback, bool overflow = true) {
			std::vector<std::vector<VectorType>> result;
			while (true) {
				const int chunkSize = chunkCallback(result.size());
				const int vectorSize = std::fmin(vector.size(), chunkSize);
				if (vectorSize < chunkSize && !overflow || !vectorSize)
					return result;
				result.push_back(std::vector<VectorType>(vector.begin(), vector.begin() + vectorSize));
				vector = std::vector<VectorType>(vector.begin() + vectorSize, vector.end());
			}
			return result;
		}

		template <typename VectorType, class LambdaType>
		std::unordered_map<std::string_view, std::vector<VectorType>> group (const std::vector<VectorType>& vector, const LambdaType& groupCallback) {
			std::unordered_map<std::string_view, std::vector<VectorType>> result;
			for (int i = 0; i < vector.size(); ++i) {
				const std::string_view group = groupCallback(vector[i], i);
				if (result.contains(group))
					result.at(group).push_back(vector[i]);
				else
					result.insert({ { group, std::vector<VectorType> { vector[i] } } });
			}
			return result;
		}

		template <typename VectorType>
		int indexOfSubvector (const std::vector<VectorType>& vector, const std::vector<VectorType>& subvector, bool wrap = false) {
			const int vectorSize = vector.size();
			const int subvectorSize = subvector.size();
			for (int i = 0; i < vectorSize; ++i) {
				int j = 0;
				for (; j < subvectorSize; ++j)
					if (!wrap && i + j >= vectorSize || vector[(i + j) % vectorSize] != subvector[j])
						break;
				if (j == subvectorSize)
					return i;
			}
			return -1;
		}

		template <typename VectorType>
		std::vector<int> indicesOfSubvector (const std::vector<VectorType>& vector, const std::vector<VectorType>& subvector, bool wrap = false) {
			std::vector<int> result;
			const int vectorSize = vector.size();
			const int subvectorSize = subvector.size();
			for (int i = 0; i < vectorSize; ++i) {
				int j = 0;
				for (; j < subvectorSize; ++j)
					if (!wrap && i + j >= vectorSize || vector[(i + j) % vectorSize] != subvector[j])
						break;
				if (j == subvectorSize)
					result.push_back(i);
			}
			return result;
		}
	}
}

#endif