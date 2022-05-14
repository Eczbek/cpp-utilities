#include "./geom.hpp"
#include "./math.hpp"
#include "./alg.hpp"

util::geom::point::point (double x, double y)
	: x(x), y(y)
{}

bool util::geom::point::operator== (const util::geom::point& point) const {
	return util::math::approx_eq(x, point.x) && util::math::approx_eq(y, point.y);
}

bool util::geom::point::operator!= (const util::geom::point& point) const {
	return !(point == *this);
}

util::geom::line::line (const util::geom::point& start, const util::geom::point& end)
	: start(start), end(end)
{}

bool util::geom::line::operator== (const util::geom::line& line) const {
	return slope() == line.slope() && contains(line.start);
}

bool util::geom::line::operator!= (const util::geom::line& line) const {
	return !(line == *this);
}

double util::geom::line::slope () const {
	return (start.y - end.y) / (start.x - end.x);
}

double util::geom::line::radians () const {
	return std::fmod(std::atan2(start.y - end.y, start.x - end.x) + M_TAU, M_PI);
}

double util::geom::line::degrees () const {
	return util::math::rad_to_deg(radians());
}

std::optional<util::geom::point> util::geom::line::intersection (const util::geom::line& line) const {
	const double a = start.x - end.x;
	const double b = start.y - end.y;
	const double c = line.start.x - line.end.x;
	const double d = line.start.y - line.end.y;
	const double e = a * d - b * c;
	if (e) {
		const double f = start.x * end.y - start.y * end.x;
		const double g = line.start.x * line.end.y - line.start.y * line.end.x;
		const util::geom::point intersection { (c * f - a * g) / e, (d * f - b * g) / e };
		if (contains(intersection) && line.contains(intersection))
			return intersection;
	}
	return std::nullopt;
}

bool util::geom::line::contains (const util::geom::point& point) const {
	const double slope = this->slope();
	return std::isinf(slope) ? point.x == start.x : util::math::approx_eq(point.y, point.x * slope - start.x * slope + start.y);
}

util::geom::ray::ray (const util::geom::point& start, const util::geom::point& end)
	: util::geom::line(start, end)
{}

bool util::geom::ray::operator== (const util::geom::ray& ray) const {
	return start == ray.start && contains(ray.end);
}

bool util::geom::ray::operator!= (const util::geom::ray& ray) const {
	return !(ray == *this);
}

bool util::geom::ray::contains (const util::geom::point& point) const {
	const double slope = this->slope();
	return (std::isinf(slope) ? point.x == start.x : util::math::approx_eq(point.y, point.x * slope - start.x * slope + start.y)) && (start.x <= end.x ? point.x >= start.x : point.x <= start.x) && (start.y <= end.y ? point.y >= start.y : point.y <= start.y);
}

util::geom::segment::segment (const util::geom::point& start, const util::geom::point& end)
	: util::geom::line(start, end)
{}

bool util::geom::segment::operator== (const util::geom::segment& segment) const {
	return start == segment.start && end == segment.end || start == segment.end && end == segment.start;
}

bool util::geom::segment::operator!= (const util::geom::segment& segment) const {
	return !(segment == *this);
}

double util::geom::segment::length () const {
	return std::hypot(start.x - end.x, start.y - end.y);
}

bool util::geom::segment::contains (const util::geom::point& point) const {
	const double slope = this->slope();
	return (std::isinf(slope) ? point.x == start.x : util::math::approx_eq(point.y, point.x * slope - start.x * slope + start.y)) && (start.x < end.x ? point.x >= start.x && point.x <= end.x : point.x <= start.x && point.x >= end.x) && (start.y < end.y ? point.y >= start.y && point.y <= end.y : point.y <= start.y && point.y >= end.y);
}

util::geom::polygon::polygon (const std::vector<util::geom::point>& points)
	: points(points)
{}

bool util::geom::polygon::operator== (const util::geom::polygon& polygon) const {
	return util::alg::match_rotated(points.begin(), points.end(), polygon.points.begin(), polygon.points.end()) || util::alg::match_rotated(points.rbegin(), points.rend(), polygon.points.begin(), polygon.points.end());
}

bool util::geom::polygon::operator!= (const util::geom::polygon& polygon) const {
	return !(polygon == *this);
}

double util::geom::polygon::area () const {
	double area = 0;
	for (int i = 0; i < points.size(); ++i) {
		const util::geom::point& current = points[i];
		const util::geom::point& next = points[(i + 1) % points.size()];
		area += current.x * next.y - next.x * current.y;
	}
	return area / 2;
}

double util::geom::polygon::perimeter () const {
	double perimeter = 0;
	for (int i = 0; i < points.size(); ++i) {
		const util::geom::point& current = points[i];
		const util::geom::point& next = points[(i + 1) % points.size()];
		perimeter += std::hypot(current.x - next.x, current.y - next.y);
	}
	return perimeter;
}

bool util::geom::polygon::contains (const util::geom::point& point) const {
	util::geom::ray ray(point, { point.x + 1, point.y });
	int intersections = 0;
	for (int i = 0; i < points.size(); ++i)
		intersections += ray.intersection(util::geom::segment(points[i], points[(i + 1) % points.size()])).has_value();
	return intersections % 2;
}
