#pragma once

#include <optional>
#include <vector>


namespace util {
	namespace geom {
		struct Point {
			double x;
			double y;

			Point(const double x = 0, const double y = 0) noexcept;

			bool operator==(const util::geom::Point& other) const noexcept;

			bool operator!=(const util::geom::Point& other) const noexcept;

			util::geom::Point rotate(const double angle, const util::geom::Point& origin = { 0, 0 }) const noexcept;
		};

		struct Line {
			util::geom::Point start;
			util::geom::Point end;

			Line(const util::geom::Point& intersection1, const util::geom::Point& intersection2) noexcept;

			Line(const util::geom::Point& intersection, const double angle) noexcept;

			bool operator==(const util::geom::Line& other) const noexcept;

			bool operator!=(const util::geom::Line& other) const noexcept;

			double slope() const noexcept;

			double interceptX() const noexcept;

			double interceptY() const noexcept;

			double angle() const noexcept;

			std::optional<util::geom::Point> intersection(const util::geom::Line& other) const noexcept;

			virtual bool contains(const util::geom::Point& point) const noexcept;
		};

		struct Ray: util::geom::Line {
			Ray(const util::geom::Point& start, const util::geom::Point& intersection) noexcept;

			Ray(const util::geom::Point& start, const double angle) noexcept;

			bool operator==(const util::geom::Ray& other) const noexcept;

			bool operator!=(const util::geom::Ray& other) const noexcept;

			bool contains(const util::geom::Point& point) const noexcept;
		};

		struct Segment: util::geom::Line {
			Segment(const util::geom::Point& start, const util::geom::Point& end) noexcept;

			bool operator==(const util::geom::Segment& other) const noexcept;

			bool operator!=(const util::geom::Segment& other) const noexcept;

			double length() const noexcept;

			bool contains(const util::geom::Point& point) const noexcept;
		};

		struct Polygon {
			std::vector<util::geom::Point> points;

			Polygon(const std::vector<util::geom::Point>& points) noexcept;

			bool operator==(const util::geom::Polygon& other) const noexcept;

			bool operator!=(const util::geom::Polygon& other) const noexcept;

			double area() const noexcept;

			double perimeter() const noexcept;

			std::vector<util::geom::Segment> sides() const noexcept;

			bool contains(const util::geom::Point& point) const noexcept;
		};

		struct Ellipse {
			util::geom::Point center;
			util::geom::Point radius;
			double rotation;

			Ellipse(const util::geom::Point& center, const util::geom::Point& radius, const double rotation = 0) noexcept;

			bool operator==(const util::geom::Ellipse& other) const noexcept;

			bool operator!=(const util::geom::Ellipse& other) const noexcept;

			double area() const noexcept;

			double perimiter() const noexcept;

			bool contains(const util::geom::Point& point) const noexcept;

			std::vector<util::geom::Point> intersections(const util::geom::Line& line) const noexcept;

			std::vector<util::geom::Point> intersections(const util::geom::Ellipse& other) const noexcept;
		};

		struct Circle: util::geom::Ellipse {
			Circle(const util::geom::Point& center, const double radius) noexcept;

			bool operator==(const util::geom::Circle& other) const noexcept;

			bool operator!=(const util::geom::Circle& other) const noexcept;

			bool contains(const util::geom::Point& point) const noexcept;
		};

		struct Rectangle: util::geom::Polygon {
			Rectangle(const util::geom::Point& corner1, const util::geom::Point& corner2) noexcept;

			Rectangle(const util::geom::Segment& segment) noexcept;

			Rectangle(const util::geom::Polygon& polygon) noexcept;

			Rectangle(const util::geom::Ellipse& ellipse) noexcept;

			Rectangle(const util::geom::Circle& circle) noexcept;

			bool operator==(const util::geom::Rectangle& other) const noexcept;

			bool operator!=(const util::geom::Rectangle& other) const noexcept;

			double width() const noexcept;

			double height() const noexcept;

			double area() const noexcept;

			double perimeter() const noexcept;

			bool contains(const util::geom::Point& point) const noexcept;
		};
	}
}
