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

		template <typename IteratorType1, typename IteratorType2>
		bool match_rotated (IteratorType1 begin1, const IteratorType1 end1, const IteratorType2 begin2, const IteratorType2 end2) {
			const auto size = std::distance(begin1, end1);
			if (size != std::distance(begin2, end2))
				return false;
			for (; begin1 != end1; ++begin1) {
				IteratorType2 copy2 = begin2;
				for (IteratorType1 copy1 = begin1; copy2 != end2; ++copy1, ++copy2) {
					if (copy1 == end1)
						std::advance(copy1, -size);
					if (*copy1 != *copy2)
						break;
				}
				if (copy2 == end2)
					return true;
			}
			return false;
		}
	}
}