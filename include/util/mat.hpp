#pragma once

#include <span>
#include <stdexcept>
#include <vector>


namespace util {
	template <typename Value>
	class Matrix {
	private:
		std::vector<std::size_t> dimensions;
		std::vector<Value> values;

	public:
		Matrix(std::span<const std::size_t> dimensions)
			: dimensions(dimensions.begin(), dimensions.end())
		{
			std::size_t size = 1;
			for (const std::size_t dimension: dimensions)
				size *= dimension;
			values.resize(size);
		}

		Matrix(std::span<const std::size_t> dimensions, std::span<const Value> values)
			: dimensions(dimensions.begin(), dimensions.end()), values(values.begin(), values.end())
		{
			std::size_t size = 1;
			for (const std::size_t dimension: dimensions)
				size *= dimension;
			if (size != values.size())
				throw std::runtime_error("Values do not match dimensions");
		}

		Value& operator[](std::span<const std::size_t> indices) {
			if (indices.size() != dimensions.size())
				throw std::runtime_error("Indices do not match dimensions");
			std::size_t index = 0;
			for (std::size_t i = 0; i < indices.size(); ++i) {
				if (indices[i] >= dimensions[i])
					throw std::runtime_error("Index out of bounds");
				index = index * dimensions[i] + indices[i];
			}
			return values[index];
		}

		const Value& operator[](std::span<const std::size_t> indices) const {
			if (indices.size() != dimensions.size())
				throw std::runtime_error("Indices do not match dimensions");
			std::size_t index = 0;
			for (std::size_t i = 0; i < indices.size(); ++i) {
				if (indices[i] >= dimensions[i])
					throw std::runtime_error("Index out of bounds");
				index = index * dimensions[i] + indices[i];
			}
			return values[index];
		}

		std::span<const Value> getValues() const {
			return values;
		}

		std::span<const std::size_t> getDimensions() const {
			return dimensions;
		}
	};
}
