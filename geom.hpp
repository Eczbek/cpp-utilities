#pragma once

namespace util {
	namespace geom {
		class point {
			public:
				double x;
				double y;

				point (double x, double y);

				bool operator== (const util::geom::point& point) const;
				bool operator!= (const util::geom::point& point) const;
		};
	}
}