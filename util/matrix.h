
#include <vector>
#include <cassert>
#include <iostream>

template <typename T>
class Matrix {
	private:
		std::vector<T> values;

	public:
		std::vector<int> dimensions;

		Matrix (const std::vector<int>& dimensions)
			: dimensions(dimensions)
		{
			int size = 1;
			for (int dimension : dimensions) {
				size *= dimension;
			}
			values = std::vector<T>(size);
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
