#pragma once

#include <random>


namespace util {
	namespace alg {
		template <typename Iterator1, typename Iterator2>
		bool rotatedMatch(Iterator1 begin1, const Iterator1 end1, const Iterator2 begin2, const Iterator2 end2) {
			const typename std::iterator_traits<Iterator1>::difference_type size = std::distance(begin1, end1);
			if (size == std::distance(begin2, end2))
				for (; begin1 != end1; ++begin1) {
					Iterator1 copy1 = begin1;
					Iterator2 copy2 = begin2;
					while (copy2 != end2) {
						if (copy1 == end1)
							std::advance(copy1, -size);
						if (*copy1 != *copy2)
							break;
						++copy1;
						++copy2;
					}
					if (copy2 == end2)
						return true;
				}
			return false;
		}
	}
}
