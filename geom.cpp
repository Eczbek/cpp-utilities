#include "./geom.hpp"
#include "./math.hpp"
#include "./alg.hpp"

util::geom::point::point (double x, double y)
	: x(x), y(y)
{}

bool util::geom::point::operator== (const util::geom::point& point) const {
	return util::math::approx_equal(x, point.x) && util::math::approx_equal(y, point.y);
}

bool util::geom::point::operator!= (const util::geom::point& point) const {
	return !operator==(point);
}

util::geom::line::line (const util::geom::point& start, const util::geom::point& end)
	: start(start), end(end)
{}

bool util::geom::line::operator== (const util::geom::line& line) const {
	return slope() == line.slope() && contains(line.start);
}

bool util::geom::line::operator!= (const util::geom::line& line) const {
	return !operator==(line);
}

double util::geom::line::slope () const {
	return (start.y - end.y) / (start.x - end.x);
}

double util::geom::line::angle_rad () const {
	return std::fmod(std::atan2(start.y - end.y, start.x - end.x) + M_TAU, M_PI);
}

double util::geom::line::angle_deg () const {
	return util::math::rad_to_deg(angle_rad());
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
		const util::geom::point intersection((c * f - a * g) / e, (d * f - b * g) / e);
		if (contains(intersection) && line.contains(intersection))
			return intersection;
	}
	return std::nullopt;
}

bool util::geom::line::contains (const util::geom::point& point) const {
	const double slope = this->slope();
	return std::isinf(slope)
		? point.x == start.x
		: util::math::approx_equal(point.y, point.x * slope - start.x * slope + start.y);
}

util::geom::ray::ray (const util::geom::point& start, const util::geom::point& end)
	: util::geom::line(start, end)
{}

bool util::geom::ray::operator== (const util::geom::ray& ray) const {
	return start == ray.start && contains(ray.end);
}

bool util::geom::ray::operator!= (const util::geom::ray& ray) const {
	return !operator==(ray);
}

bool util::geom::ray::contains (const util::geom::point& point) const {
	const double slope = this->slope();
	return (std::isinf(slope)
		? point.x == start.x
		: util::math::approx_equal(point.y, point.x * slope - start.x * slope + start.y))
		&& (start.x <= end.x
			? point.x >= start.x
			: point.x <= start.x)
		&& (start.y <= end.y
			? point.y >= start.y
			: point.y <= start.y);
}

util::geom::segment::segment (const util::geom::point& start, const util::geom::point& end)
	: util::geom::line(start, end)
{}

bool util::geom::segment::operator== (const util::geom::segment& segment) const {
	return start == segment.start && end == segment.end || start == segment.end && end == segment.start;
}

bool util::geom::segment::operator!= (const util::geom::segment& segment) const {
	return !operator==(segment);
}

double util::geom::segment::length () const {
	return std::hypot(start.x - end.x, start.y - end.y);
}

bool util::geom::segment::contains (const util::geom::point& point) const {
	const double slope = this->slope();
	return (std::isinf(slope)
		? point.x == start.x
		: util::math::approx_equal(point.y, point.x * slope - start.x * slope + start.y))
		&& (start.x < end.x
			? point.x >= start.x && point.x <= end.x
			: point.x <= start.x && point.x >= end.x)
		&& (start.y < end.y
			? point.y >= start.y && point.y <= end.y
			: point.y <= start.y && point.y >= end.y);
}

util::geom::polygon::polygon (const std::vector<util::geom::point>& points)
	: points(points)
{}

bool util::geom::polygon::operator== (const util::geom::polygon& polygon) const {
	return util::alg::rotated_match(points.begin(), points.end(), polygon.points.begin(), polygon.points.end()) || util::alg::rotated_match(points.rbegin(), points.rend(), polygon.points.begin(), polygon.points.end());
}

bool util::geom::polygon::operator!= (const util::geom::polygon& polygon) const {
	return !operator==(polygon);
}

double util::geom::polygon::area () const {
	double area = 0;
	for (std::size_t i = 0; i < points.size(); ++i) {
		const util::geom::point& current = points[i];
		const util::geom::point& next = points[(i + 1) % points.size()];
		area += current.x * next.y - next.x * current.y;
	}
	return area / 2;
}

double util::geom::polygon::perimeter () const {
	double perimeter = 0;
	for (std::size_t i = 0; i < points.size(); ++i) {
		const util::geom::point& current = points[i];
		const util::geom::point& next = points[(i + 1) % points.size()];
		perimeter += std::hypot(current.x - next.x, current.y - next.y);
	}
	return perimeter;
}

bool util::geom::polygon::contains (const util::geom::point& point) const {
	util::geom::ray ray(point, { point.x + 1, point.y });
	std::size_t intersections = 0;
	for (std::size_t i = 0; i < points.size(); ++i)
		intersections += ray.intersection(util::geom::segment(points[i], points[(i + 1) % points.size()])).has_value();
	return intersections % 2;
}

util::geom::rectangle::rectangle (const util::geom::point& corner1, const util::geom::point& corner2)
	: util::geom::polygon({ corner1, { corner2.x, corner1.y }, corner2, { corner1.x, corner2.y } })
{}

bool util::geom::rectangle::operator== (const util::geom::rectangle& rectangle) const {
	return points[0] == rectangle.points[0] && points[2] == rectangle.points[2] || points[0] == rectangle.points[2] && points[2] == rectangle.points[0];
}

bool util::geom::rectangle::operator!= (const util::geom::rectangle& rectangle) const {
	return !operator==(rectangle);
}

double util::geom::rectangle::width () const {
	return std::abs(points[0].x - points[2].x);
}

double util::geom::rectangle::height () const {
	return std::abs(points[0].y - points[2].y);
}

double util::geom::rectangle::area () const {
	return width() * height();
}

double util::geom::rectangle::perimeter () const {
	return 2 * (width() + height());
}

bool util::geom::rectangle::contains (const util::geom::point& point) const {
	return (point.x >= points[0].x && point.x <= points[2].x || point.x <= points[0].x && point.x >= points[2].x) && (point.y >= points[0].y && point.y <= points[2].y || point.y <= points[0].y && point.y >= points[2].y);
}
