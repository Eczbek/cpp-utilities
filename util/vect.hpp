#pragma once

#include <vector>
#include <cmath>
#include <string_view>
#include <unordered_map>

namespace util {
	namespace vect {
		template <typename VectorType>
		std::vector<std::vector<VectorType>> chunk (std::vector<VectorType> vector, const int chunkSize, const bool overflow = true) {
			std::vector<std::vector<VectorType>> chunked;
			while (true) {
				const int vectorSize = std::fmin(vector.size(), chunkSize);
				if (vectorSize < chunkSize && !overflow || !vectorSize)
					return chunked;
				chunked.push_back(std::vector<VectorType>(vector.begin(), vector.begin() + vectorSize));
				vector = std::vector<VectorType>(vector.begin() + vectorSize, vector.end());
			}
		}

		template <typename VectorType, class CallbackType>
		std::vector<std::vector<VectorType>> chunk (std::vector<VectorType> vector, const CallbackType& getChunkSize, const bool overflow = true) {
			std::vector<std::vector<VectorType>> chunked;
			while (true) {
				const int chunkSize = getChunkSize(chunked.size());
				const int vectorSize = std::fmin(vector.size(), chunkSize);
				if (vectorSize < chunkSize && !overflow || !vectorSize)
					return chunked;
				chunked.push_back(std::vector<VectorType>(vector.begin(), vector.begin() + vectorSize));
				vector = std::vector<VectorType>(vector.begin() + vectorSize, vector.end());
			}
		}
		
		template <typename KeyType = std::string_view, typename VectorType, class CallbackType>
		std::unordered_map<KeyType, std::vector<VectorType>> group (const std::vector<VectorType>& values, const CallbackType& getGroup) {
			std::unordered_map<KeyType, std::vector<VectorType>> groups;
			for (int i = 0; i < values.size(); ++i)
				groups[getGroup(values[i], i)].push_back(values[i]);
			return groups;
		}
	}
}