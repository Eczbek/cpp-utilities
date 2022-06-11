#pragma once

#include <optional>
#include <vector>


namespace util {
	namespace geom {
		struct Point {
			double x;
			double y;

			Point(const double x = 0, const double y = 0);

			bool operator==(const util::geom::Point& other) const;

			bool operator!=(const util::geom::Point& other) const;

			util::geom::Point rotate(const double angle, const util::geom::Point& origin = { 0, 0 }) const;
		};

		struct Line {
			util::geom::Point start;
			util::geom::Point end;

			Line(const util::geom::Point& intersection1, const util::geom::Point& intersection2);

			Line(const util::geom::Point& intersection, const double angle);

			bool operator==(const util::geom::Line& other) const;

			bool operator!=(const util::geom::Line& other) const;

			double slope() const;

			double interceptX() const;

			double interceptY() const;

			double angle() const;

			std::optional<util::geom::Point> intersection(const util::geom::Line& other) const;

			virtual bool contains(const util::geom::Point& point) const;
		};

		struct Ray: util::geom::Line {
			Ray(const util::geom::Point& start, const util::geom::Point& intersection);

			Ray(const util::geom::point& start, const double angle);

			bool operator==(const util::geom::Ray& other) const;

			bool operator!=(const util::geom::Ray& other) const;

			bool contains(const util::geom::Point& point) const;
		};

		struct Segment: util::geom::Line {
			Segment(const util::geom::Point& start, const util::geom::Point& end);

			bool operator==(const util::geom::Segment& other) const;

			bool operator!=(const util::geom::Segment& other) const;

			double length() const;

			bool contains(const util::geom::Point& point) const;
		};

		struct Polygon {
			std::vector<util::geom::Point> points;

			polygon(const std::vector<util::geom::Point>& points);

			bool operator==(const util::geom::Polygon& other) const;

			bool operator!=(const util::geom::Polygon& other) const;

			double area() const;

			double perimeter() const;

			std::vector<util::geom::Segment> sides() const;

			bool contains(const util::geom::Point& point) const;
		};

		struct Ellipse {
			util::geom::Point center;
			util::geom::Point radius;
			double rotation;

			Ellipse(const util::geom::Point& center, const util::geom::Point& radius, const double rotation = 0);

			bool operator==(const util::geom::Ellipse& other) const;

			bool operator!=(const util::geom::Ellipse& other) const;

			double area() const;

			double perimiter() const;

			bool contains(const util::geom::Point& point) const;

			std::vector<util::geom::Point> intersections(const util::geom::Line& line) const;

			std::vector<util::geom::Point> intersections(const util::geom::Ellipse& other) const;
		};

		struct Circle: util::geom::Ellipse {
			Circle(const util::geom::Point& center, const double radius);

			bool operator==(const util::geom::Circle& other) const;

			bool operator!=(const util::geom::Circle& other) const;

			bool contains(const util::geom::Point& point) const;
		};

		struct Rectangle: util::geom::Polygon {
			Rectangle(const util::geom::Point& corner1, const util::geom::Point& corner2);

			Rectangle(const util::geom::Segment& segment);

			Rectangle(const util::geom::Polygon& polygon);

			Rectangle(const util::geom::Ellipse& ellipse);

			Rectangle(const util::geom::Circle& circle);

			bool operator==(const util::geom::Rectangle& other) const;

			bool operator!=(const util::geom::Rectangle& other) const;

			double width() const;

			double height() const;

			double area() const;

			double perimeter() const;

			bool contains(const util::geom::Point& point) const;
		};
	}
}
