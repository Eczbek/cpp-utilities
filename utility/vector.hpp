#ifndef UTIL_VECTOR_H
#define UTIL_VECTOR_H

#include <vector>
#include <cmath>
#include <string_view>
#include <unordered_map>

namespace utility {
	namespace vector {
		template <typename T>
		std::vector<std::vector<T>> chunk (std::vector<T> vector, int chunkSize, bool overflow = true) {
			std::vector<std::vector<T>> result;
			while (true) {
				const int vectorSize = std::fmin(vector.size(), chunkSize);
				if (vectorSize < chunkSize && !overflow || !vectorSize)
					return result;
				result.push_back(std::vector<T>(vector.begin(), vector.begin() + vectorSize));
				vector = std::vector<T>(vector.begin() + vectorSize, vector.end());
			}
		}

		template <typename T, class C>
		std::vector<std::vector<T>> chunk (std::vector<T> vector, const C& chunkCallback, bool overflow = true) {
			std::vector<std::vector<T>> result;
			while (true) {
				const int chunkSize = chunkCallback(result.size());
				const int vectorSize = std::fmin(vector.size(), chunkSize);
				if (vectorSize < chunkSize && !overflow || !vectorSize)
					return result;
				result.push_back(std::vector<T>(vector.begin(), vector.begin() + vectorSize));
				vector = std::vector<T>(vector.begin() + vectorSize, vector.end());
			}
			return result;
		}

		template <typename T, class C>
		std::unordered_map<std::string_view, std::vector<T>> group (const std::vector<T>& vector, const C& groupCallback) {
			std::unordered_map<std::string_view, std::vector<T>> result;
			for (int i = 0; i < vector.size(); ++i) {
				const std::string_view group = groupCallback(vector[i], i);
				if (result.contains(group))
					result.at(group).push_back(vector[i]);
				else
					result.insert({ { group, std::vector<T> { vector[i] } } });
			}
			return result;
		}
	}
}

#endif