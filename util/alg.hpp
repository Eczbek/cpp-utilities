#pragma once

#include "./math.hpp"
#include <random>

namespace util {
	namespace alg {
		template <typename IteratorType, class CallbackType>
		IteratorType bin_srch (IteratorType begin, IteratorType end, const CallbackType& getSearchDirection) {
			const IteratorType temp = end;
			while (true) {
				IteratorType middle = begin;
				const auto size = std::distance(begin, end);
				std::advance(middle, size / 2);
				const int check = util::math::sign(getSearchDirection(*middle));
				if (!check)
					return middle;
				if (size < 2)
					return temp;
				if (check < 0)
					begin = ++middle;
				else
					end = middle;
			}
		}

		template <typename IteratorType, typename RandomGeneratorType>
		void shuffle (IteratorType begin, const IteratorType end, RandomGeneratorType randomGenerator) {
			for (auto size = std::distance(begin, end); begin != end; ++begin) {
				IteratorType temp = begin;
				std::advance(temp, std::uniform_int_distribution<>(0, --size)(randomGenerator));
				std::swap(*temp, *begin);
			}
		}
	}
}