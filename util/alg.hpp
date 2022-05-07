#pragma once

#include <random>

namespace util {
	namespace alg {
		template <typename IteratorType, class LambdaType>
		int bin_srch (IteratorType begin, IteratorType end, const LambdaType& searchCallback) {
			const IteratorType temp = begin;
			while (true) {
				IteratorType middle = begin;
				const int distance = std::distance(begin, end);
				std::advance(middle, distance / 2);
				const int check = searchCallback(*middle);
				if (!check)
					return std::distance(temp, middle);
				if (distance < 2)
					return -1;
				if (check < 0)
					begin = ++middle;
				else
					end = middle;
			}
		}

		template <typename IteratorType>
		void shuffle (IteratorType begin, const IteratorType end) {
			std::mt19937 rng32 (std::random_device{}());
			for (auto size = std::distance(begin, end); begin != end; ++begin) {
				IteratorType temp = begin;
				std::advance(temp, std::uniform_int_distribution<>(0, --size)(rng32));
				std::swap(*temp, *begin);
			}
		}
	}
}
