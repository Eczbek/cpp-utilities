#pragma once

#include <array>
#include <limits>


namespace util {
	template <typename Key, typename Value>
	struct OrderedMap {
		std::array<Value, std::numeric_limits<Key>::max() - std::numeric_limits<Key>::min() + 1> values;

		Value& operator[](const Key key) {
			return values[key - std::numeric_limits<Key>::min()];
		}
	};
}
