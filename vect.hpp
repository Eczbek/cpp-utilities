#pragma once

#include <cmath>
#include <string>
#include <unordered_map>
#include <vector>


namespace util {
	namespace vect {
		template <typename Value>
		std::vector<std::vector<Value>> chunk(const std::vector<Value>& values, const int chunkSize, const bool overflow = true) {
			std::vector<std::vector<Value>> chunks;
			std::size_t i = 0;
			while (true) {
				const std::size_t vectorSize = std::fmin(values.size(), chunkSize);
				if (!vectorSize || !overflow && vectorSize < chunkSize)
					return chunks;
				chunks.push_back(std::vector<Value>(values.begin() + i, values.begin() + i + vectorSize));
				i += vectorSize;
			}
		}

		template <typename Value, class Callback>
		std::vector<std::vector<Value>> chunk(const std::vector<Value>& values, const Callback& getChunkSize, const bool overflow = true) {
			std::vector<std::vector<Value>> chunks;
			std::size_t i = 0;
			while (true) {
				const std::size_t chunkSize = getChunkSize(chunks.size());
				const std::size_t vectorSize = std::fmin(values.size(), chunkSize);
				if (!vectorSize || !overflow && vectorSize < chunkSize)
					return chunks;
				chunks.push_back(std::vector<Value>(values.begin() + i, values.begin() + i + vectorSize));
				i += vectorSize;
			}
		}
		
		template <typename Key = std::string, typename Value, class Callback>
		std::unordered_map<Key, std::vector<Value>> group(const std::vector<Value>& values, const Callback& getGroup) {
			std::unordered_map<Key, std::vector<Value>> groups;
			for (std::size_t i = 0; i < values.size(); ++i)
				groups[getGroup(values[i], i)].push_back(values[i]);
			return groups;
		}

		template <typename Value>
		std::vector<std::vector<Value>> rotate_cw(const std::vector<std::vector<Value>>& values) {
			std::vector<std::vector<Value>> rotated;
			for (std::size_t y = 0; y < values[0].size(); ++y) {
				std::vector<Value> row;
				for (std::size_t x = values.size(); x > 0; --x)
					row.push_back(values[x - 1][y]);
				rotated.push_back(row);
			}
			return rotated;
		}

		template <typename Value>
		std::vector<std::vector<Value>> rotate_ccw(const std::vector<std::vector<Value>>& values) {
			std::vector<std::vector<Value>> rotated;
			for (std::size_t y = values[0].size() - 1; y >= 0; --y) {
				std::vector<Value> row;
				for (std::size_t x = 0; x < values.size(); ++x)
					row.push_back(values[x][y]);
				rotated.push_back(row);
			}
			return rotated;
		}
	}
}