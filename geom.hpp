#pragma once
#include <optional>
#include <vector>

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

				virtual bool contains (const util::geom::point& point) const;
		};

		class ray: public util::geom::line {
			public:
				ray (const util::geom::point& start, const util::geom::point& end);

				bool operator== (const util::geom::ray& ray) const;

				bool operator!= (const util::geom::ray& ray) const;

				virtual bool contains (const util::geom::point& point) const;
		};

		class segment: public util::geom::line {
			public:
				segment (const util::geom::point& start, const util::geom::point& end);

				bool operator== (const util::geom::segment& segment) const;

				bool operator!= (const util::geom::segment& segment) const;

				double length () const;

				virtual bool contains (const util::geom::point& point) const;
		};

		class polygon {
			public:
				std::vector<util::geom::point> points;

				polygon (const std::vector<util::geom::point>& points);

				bool operator== (const util::geom::polygon& polygon) const;

				bool operator!= (const util::geom::polygon& polygon) const;

				double area () const;

				double perimeter () const;

				virtual bool contains (const util::geom::point& point) const;
		};

		class rectangle: public util::geom::polygon {
			public:
				rectangle (const util::geom::point& corner1, const util::geom::point& corner2);

				bool operator== (const util::geom::rectangle& rectangle) const;

				bool operator!= (const util::geom::rectangle& rectangle) const;

				double width () const;

				double height () const;

				double area () const;

				double perimeter () const;

				virtual bool contains (const util::geom::point& point) const;
		};
	}
}