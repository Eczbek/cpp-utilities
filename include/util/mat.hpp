#pragma once

#include <cassert>
#include <vector>


namespace util {
	template <typename Value>
	class Matrix {
	private:
		std::vector<Value> values;
		std::vector<std::size_t> dimensions;

	public:
		Matrix(const std::vector<std::size_t>& dimensions)
			: dimensions(dimensions)
		{
			std::size_t size = 1;
			for (const std::size_t dimension: dimensions)
				size *= dimension;
			values.resize(size);
		}

		Matrix(const std::vector<std::size_t>& dimensions, const std::vector<Value>& values)
			: values(values), dimensions(dimensions)
		{
			std::size_t size = 1;
			for (const std::size_t dimension: dimensions)
				size *= dimension;
			assert(size == values.size());
		}

		Value& operator[](const std::vector<std::size_t>& indices) {
			assert(indices.size() == dimensions.size());
			std::size_t index = 0;
			for (std::size_t i = 0; i < indices.size(); ++i) {
				assert(indices[i] < dimensions[i]);
				index = index * dimensions[i] + indices[i];
			}
			return values[index];
		}

		const Value& operator[](const std::vector<std::size_t>& indices) const {
			assert(indices.size() == dimensions.size());
			std::size_t index = 0;
			for (std::size_t i = 0; i < indices.size(); ++i) {
				assert(indices[i] < dimensions[i]);
				index = index * dimensions[i] + indices[i];
			}
			return values[index];
		}

		const std::vector<Value>& values() const {
			return values;
		}

		const std::vector<std::size_t>& dimensions() const {
			return dimensions;
		}
	};
}
