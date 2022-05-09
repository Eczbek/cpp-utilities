#pragma once

#include "./math.hpp"
#include <random>

namespace util {
	namespace alg {
		template <typename Iterator, class Callback>
		Iterator bin_srch (Iterator begin, Iterator end, const Callback& getSearchDirection) {
			const Iterator temp = end;
			while (true) {
				Iterator middle = begin;
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

		template <typename Iterator, typename RandomGenerator>
		void shuffle (Iterator begin, const Iterator end, RandomGenerator randomGenerator) {
			for (auto size = std::distance(begin, end); begin != end; ++begin) {
				Iterator temp = begin;
				std::advance(temp, std::uniform_int_distribution<>(0, --size)(randomGenerator));
				std::swap(*temp, *begin);
			}
		}

		template <typename Iterator1, typename Iterator2>
		bool match_rotated (Iterator1 begin1, const Iterator1 end1, const Iterator2 begin2, const Iterator2 end2) {
			const auto size = std::distance(begin1, end1);
			if (size != std::distance(begin2, end2))
				return false;
			for (; begin1 != end1; ++begin1) {
				Iterator2 copy2 = begin2;
				for (Iterator1 copy1 = begin1; copy2 != end2; ++copy1, ++copy2) {
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