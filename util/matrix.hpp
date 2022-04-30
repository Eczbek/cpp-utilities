#ifndef UTIL_MATRIX_HPP
#define UTIL_MATRIX_HPP

#include <vector>
#include <cassert>

template <typename T>
class Matrix {
	public:
		std::vector<int> dimensions;
		std::vector<T> values;

		Matrix (const std::vector<int>& dimensions)
			: dimensions(dimensions)
		{
			int size = 1;
			for (int dimension : dimensions)
				size *= dimension;
			values = std::vector<T>(size);
		}

		Matrix (const std::vector<int>& dimensions, const std::vector<T>& values)
			: dimensions(dimensions), values(values)
		{
			int size = 1;
			for (int dimension : dimensions)
				size *= dimension;
			assert(values.size() == size);
		}

		T& operator() (const std::vector<int>& indices) {
			assert(indices.size() == dimensions.size());
			int index = 0;
			for (int i = 0; i < indices.size(); ++i) {
				assert(indices[i] < dimensions[i]);
				index = index * dimensions[i] + indices[i];
			}
			return values[index];
		}
};

#endif