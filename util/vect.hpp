#pragma once

#include <vector>
#include <cmath>
#include <string_view>
#include <unordered_map>

namespace util {
	namespace vect {
		template <typename VectorType>
		std::vector<std::vector<VectorType>> chunk (const std::vector<VectorType>& values, const int chunkSize, const bool overflow = true) {
			std::vector<std::vector<VectorType>> chunks;
			int i = 0;
			while (true) {
				const int vectorSize = std::fmin(values.size(), chunkSize);
				if (!vectorSize || !overflow && vectorSize < chunkSize)
					return chunks;
				chunks.push_back(std::vector<VectorType>(values.begin() + i, values.begin() + i + vectorSize));
				i += vectorSize;
			}
		}

		template <typename VectorType, class CallbackType>
		std::vector<std::vector<VectorType>> chunk (const std::vector<VectorType>& values, const CallbackType& getChunkSize, const bool overflow = true) {
			std::vector<std::vector<VectorType>> chunks;
			int i = 0;
			while (true) {
				const int chunkSize = getChunkSize(chunks.size());
				const int vectorSize = std::fmin(values.size(), chunkSize);
				if (!vectorSize || !overflow && vectorSize < chunkSize)
					return chunks;
				chunks.push_back(std::vector<VectorType>(values.begin() + i, values.begin() + i + vectorSize));
				i += vectorSize;
			}
		}
		
		template <typename KeyType = std::string, typename VectorType, class CallbackType>
		std::unordered_map<KeyType, std::vector<VectorType>> group (const std::vector<VectorType>& values, const CallbackType& getGroup) {
			std::unordered_map<KeyType, std::vector<VectorType>> groups;
			for (int i = 0; i < values.size(); ++i)
				groups[getGroup(values[i], i)].push_back(values[i]);
			return groups;
		}
	}
}