#pragma once

#include <random>

namespace utility {
	namespace algorithm {
		template <typename IteratorType, class LambdaType>
		int binarySearch (IteratorType begin, IteratorType end, const LambdaType& searchCallback) {
			const IteratorType start = begin;
			while (true) {
				const IteratorType middle = begin + (end - begin) / 2;
				const int check = searchCallback(*middle);
				if (!check)
					return std::distance(start, middle);
				if (end - begin < 2)
					return -1;
				if (check < 0)
					begin = middle + 1;
				else
					end = middle;
			}
		}

		template <typename IteratorType>
		void shuffle (IteratorType begin, IteratorType end) {
			std::mt19937 rng32 (std::random_device{}());
			for (auto size = std::distance(begin, end); begin != end; ++begin) {
				IteratorType temp = begin;
				std::advance(temp, std::uniform_int_distribution<>(0, --size)(rng32));
				std::swap(*temp, *begin);
			}
		}
	}
}
