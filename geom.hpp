#pragma once
#include <optional>

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

		class line {
			public:
				util::geom::point start;
				util::geom::point end;

				line (const util::geom::point& start, const util::geom::point& end);

				bool operator== (const util::geom::line& line) const;

				bool operator!= (const util::geom::line& line) const;

				double slope () const;

				double radians () const;

				double degrees () const;

				std::optional<util::geom::point> intersection (const util::geom::line& line) const;

				bool contains (const util::geom::point& point) const;
		};

		class ray: public util::geom::line {
			public:
				ray (const util::geom::point& start, const util::geom::point& end);

				bool operator== (const util::geom::ray& ray) const;

				bool operator!= (const util::geom::ray& ray) const;

				bool contains (const util::geom::point& point) const;
		};
	}
}