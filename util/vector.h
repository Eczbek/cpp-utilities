#ifndef UTIL_VECTOR_H
#define UTIL_VECTOR_H

#include <vector>


namespace util {
	namespace vector {
		template <typename T>
		std::vector<T> erase (std::vector<T> vector, int start, int erase = 1) {
			if (start < 0) {
				start += vector.size() + 1;
			}
			vector.erase(vector.begin() + start, vector.begin() + start + erase);
			return vector;
		}

		template <typename T>
		std::vector<T> splice (std::vector<T> vector, int start, int erase, T insert) {
			if (start < 0) {
				start += vector.size() + 1;
			}
			vector = util::vector::erase(vector, start, erase);
			vector.insert(vector.begin() + start, insert);
			return vector;
		}

		template <typename T>
		std::vector<T> splice (std::vector<T> vector, int start, int erase, std::vector<T> insert) {
			if (start < 0) {
				start += vector.size() + 1;
			}
			vector = util::vector::erase(vector, start, erase);
			vector.insert(vector.begin() + start, insert.begin(), insert.end());
			return vector;
		}

		template <typename T>
		std::vector<T> slice (std::vector<T> vector, int start, int end = -1) {
			if (start < 0) {
				start += vector.size() + 1;
			}
			if (end < 0) {
				end += vector.size() + 1;
			}
			std::vector<T> result;
			result.insert(result.begin(), vector.begin() + start, vector.begin() + end);
			return result;
		}
	}
}

#endif