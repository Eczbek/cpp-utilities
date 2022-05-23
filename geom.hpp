#pragma once

#include <optional>
#include <vector>


namespace util {
	namespace geom {
		struct point {
			double x;
			double y;

			point(double x, double y);

			bool operator==(const util::geom::point& point) const;

			bool operator!=(const util::geom::point& point) const;
		};

		struct line {
			util::geom::point start;
			util::geom::point end;

			line(const util::geom::point& start, const util::geom::point& end);

			bool operator==(const util::geom::line& line) const;

			bool operator!=(const util::geom::line& line) const;

			double slope() const;

			double angle_rad() const;

			double angle_deg() const;

			std::optional<util::geom::point> intersection(const util::geom::line& line) const;

			virtual bool contains(const util::geom::point& point) const;
		};

		struct ray: util::geom::line {
			ray(const util::geom::point& start, const util::geom::point& end);

			bool operator==(const util::geom::ray& ray) const;

			bool operator!=(const util::geom::ray& ray) const;

			virtual bool contains(const util::geom::point& point) const;
		};

		struct segment: util::geom::line {
			segment(const util::geom::point& start, const util::geom::point& end);

			bool operator==(const util::geom::segment& segment) const;

			bool operator!=(const util::geom::segment& segment) const;

			double length() const;

			virtual bool contains(const util::geom::point& point) const;
		};

		struct polygon {
			std::vector<util::geom::point> points;

			polygon(const std::vector<util::geom::point>& points);

			bool operator==(const util::geom::polygon& polygon) const;

			bool operator!=(const util::geom::polygon& polygon) const;

			double area() const;

			double perimeter() const;

			virtual bool contains(const util::geom::point& point) const;
		};

		struct rectangle: util::geom::polygon {
			rectangle(const util::geom::point& corner1, const util::geom::point& corner2);

			bool operator==(const util::geom::rectangle& rectangle) const;

			bool operator!=(const util::geom::rectangle& rectangle) const;

			double width() const;

			double height() const;

			double area() const;

			double perimeter() const;

			virtual bool contains(const util::geom::point& point) const;
		};
	}
}