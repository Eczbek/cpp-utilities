#pragma once
#include <optional>

namespace util {
	namespace geom {
		struct point {
			double x;
			double y;

			bool operator== (const util::geom::point& point) const;

			bool operator!= (const util::geom::point& point) const;
		};

		struct line {
			util::geom::point start;
			util::geom::point end;

			bool operator== (const util::geom::line& line) const;

			bool operator!= (const util::geom::line& line) const;

			double get_slope () const;

			double get_radians () const;

			double get_degrees () const;

			std::optional<util::geom::point> get_intersection (const util::geom::line& line) const;

			bool contains_point (const util::geom::point& point) const;
		};
	}
}