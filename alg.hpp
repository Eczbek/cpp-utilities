#pragma once

#include <random>


namespace util {
	namespace alg {
		template <typename Iterator, typename RandomGenerator>
		void shuffle(Iterator begin, const Iterator end, RandomGenerator randomGenerator) {
			for (typename std::Iterator_traits<Iterator>::difference_type size = std::distance(begin, end); begin != end; ++begin) {
				Iterator temp = begin;
				std::advance(temp, std::uniform_int_distribution<>(0, --size)(randomGenerator));
				std::swap(*temp, *begin);
			}
		}

		template <typename Iterator1, typename Iterator2>
		bool rotated_match(Iterator1 begin1, const Iterator1 end1, const Iterator2 begin2, const Iterator2 end2) {
			const typename std::Iterator_traits<Iterator1>::difference_type size = std::distance(begin1, end1);
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