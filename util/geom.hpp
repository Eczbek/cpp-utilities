#pragma once

namespace util {
	namespace geom {
		class point {
			public:
				double x;
				double y;
				bool valid = true;

				point (double x, double y);
				point ();

				bool operator== (const point& point) const;
				bool operator!= (const point& point) const;
		};
	}
}