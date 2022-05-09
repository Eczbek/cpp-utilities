#pragma once

#include <vector>
#include <cmath>
#include <string_view>
#include <unordered_map>
#include <algorithm>

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

		template <typename VectorType>
		bool match_rotated (const std::vector<VectorType>& values1, const std::vector<VectorType>& values2) {
			const int size1 = values1.size();
			const int size2 = values2.size();
			if (size1 != size2)
				return false;
			for (int i = 0; i < size1; ++i) {
				int j = 0;
				for (; j < size2; ++j)
					if (values1[(i + j) % size1] != values2[j])
						break;
				if (j == size2)
					return true;
			}
			return false;
		}

		template <typename VectorType>
		bool match_rotated_reversed (const std::vector<VectorType>& values1, const std::vector<VectorType>& values2) {
			return util::vect::match_rotated(values1, values2) || util::vect::match_rotated(std::vector<VectorType>(values1.rbegin(), values1.rend()), values2);
		}

		template <typename VectorType>
		std::vector<std::vector<VectorType>> rotate_cw (const std::vector<std::vector<VectorType>>& values) {
			std::vector<std::vector<VectorType>> rotated;
			for (int y = 0; y < values[0].size(); ++y) {
				std::vector<VectorType> row;
				for (int x = values.size() - 1; x >= 0; --x)
					row.push_back(values[x][y]);
				rotated.push_back(row);
			}
			return rotated;
		}

		template <typename VectorType>
		std::vector<std::vector<VectorType>> rotate_ccw (const std::vector<std::vector<VectorType>>& values) {
			std::vector<std::vector<VectorType>> rotated;
			for (int y = values[0].size() - 1; y >= 0; --y) {
				std::vector<VectorType> row;
				for (int x = 0; x < values.size(); ++x)
					row.push_back(values[x][y]);
				rotated.push_back(row);
			}
			return rotated;
		}
	}
}