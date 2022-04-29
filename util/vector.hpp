#ifndef UTIL_VECTOR_H
#define UTIL_VECTOR_H

#include <vector>
#include <cassert>
#include <algorithm>

namespace util {
	namespace vector {
		template <typename T>
		const std::vector<T>& erase (std::vector<T>& vector, int index, int erase = 1) {
			int size = vector.size();
			if (index < 0)
				index += size + 1;
			assert(index >= 0 && index < size && erase >= 0 && index + erase < size);
			vector.erase(vector.begin() + index, vector.begin() + index + erase);
			return vector;
		}

		template <typename T>
		const std::vector<T>& insert (std::vector<T>& vector, int index, const T& value) {
			int size = vector.size();
			if (index < 0)
				index += size + 1;
			assert(index >= 0 && index <= size);
			vector.insert(vector.begin() + index, value);
			return vector;
		}

		template <typename T>
		const std::vector<T>& insert (std::vector<T>& vector, int index, const std::vector<T>& values) {
			int size = vector.size();
			if (index < 0)
				index += size + 1;
			assert(index >= 0 && index <= size);
			vector.insert(vector.begin() + index, values.begin(), values.end());
			return vector;
		}

		template <typename T>
		std::vector<T> slice (const std::vector<T>& vector, int start) {
			int size = vector.size();
			if (start < 0)
				start += size + 1;
			assert(start >= 0 && start < size);
			return std::vector<T>(vector.begin() + start, vector.end());
		}

		template <typename T>
		std::vector<T> slice (const std::vector<T>& vector, int start, int end) {
			int size = vector.size();
			if (start < 0)
				start += size + 1;
			if (end < 0)
				end += size + 1;
			assert(start >= 0 && start < size && end >= start && end < size);
			return std::vector<T>(vector.begin() + start, vector.begin() + end);
		}

		template <typename T>
		bool includes (const std::vector<T>& vector, const T& value) {
			return std::find(vector.begin(), vector.end(), value) != vector.end();
		}

		template <typename T, class C>
		std::vector<T> map (const std::vector<T>& vector, const C& mapCallback) {
			std::vector<T> result;
			for (int i = 0; i < vector.size(); ++i)
				result.push_back(mapCallback(vector[i], i));
			return result;
		}

		template <typename T, class C>
		std::vector<T> filter (const std::vector<T>& vector, const C& filterCallback) {
			std::vector<T> result;
			for (int i = 0; i < vector.size(); ++i)
				if (filterCallback(vector[i], i))
					result.push_back(vector[i]);
			return result;
		}
	}
}

#endif