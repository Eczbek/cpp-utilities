#include "./geom.hpp"

#include "./alg.hpp"
#include "./math.hpp"
#include "./num.hpp"


util::geom::point::point(const double x, const double y)
	: x(x), y(y)
{}

bool util::geom::point::operator==(const util::geom::point& other) const {
	return util::math::approx_equal(x, other.x) && util::math::approx_equal(y, other.y);
}

bool util::geom::point::operator!=(const util::geom::point& other) const {
	return !operator==(other);
}

util::geom::line::line(const util::geom::point& start, const util::geom::point& end)
	: start(start), end(end)
{}

util::geom::line::line(const util::geom::point& start, const double angle)
	: start(start)
{
	if (util::math::approx_equal(std::fmod(angle + std::numbers::pi / 2, std::numbers::pi), 0.0))
		end = util::geom::point(start.x, start.y - 1);
	else 
		end = util::geom::point(start.x + 1, std::tan(angle));
}

bool util::geom::line::operator==(const util::geom::line& other) const {
	return slope() == other.slope() && contains(other.start);
}

bool util::geom::line::operator!=(const util::geom::line& other) const {
	return !operator==(other);
}

double util::geom::line::slope() const {
	return (start.y - end.y) / (start.x - end.x);
}

double util::geom::line::angle() const {
	return std::fmod(std::atan2(start.y - end.y, start.x - end.x) + util::num::tau, std::numbers::pi);
}

std::optional<util::geom::point> util::geom::line::intersection(const util::geom::line& other) const {
	const double a = (start.x - end.x) * (other.start.y - other.end.y) - (start.y - end.y) * (other.start.x - other.end.x);
	if (a) {
		const util::geom::point intersection(((other.start.x - other.end.x) * (start.x * end.y - start.y * end.x) - (start.x - end.x) * (other.start.x * other.end.y - other.start.y * other.end.x)) / a, ((other.start.y - other.end.y) * (start.x * end.y - start.y * end.x) - (start.y - end.y) * (other.start.x * other.end.y - other.start.y * other.end.x)) / a);
		if (contains(intersection) && other.contains(intersection))
			return intersection;
	}
	return std::nullopt;
}

bool util::geom::line::contains(const util::geom::point& other) const {
	const double slope = this->slope();
	return std::isinf(slope)
		? util::math::approx_equal(other.x, start.x)
		: util::math::approx_equal(other.y, other.x * slope - start.x * slope + start.y);
}

util::geom::ray::ray(const util::geom::point& start, const util::geom::point& end)
	: util::geom::line(start, end)
{}

util::geom::ray::ray(const util::geom::point& start, const double angle)
	: util::geom::line(start, angle)
{}

bool util::geom::ray::operator==(const util::geom::ray& other) const {
	return start == other.start && contains(other.end);
}

bool util::geom::ray::operator!=(const util::geom::ray& other) const {
	return !operator==(other);
}

bool util::geom::ray::contains(const util::geom::point& other) const {
	const double slope = this->slope();
	return (std::isinf(slope)
		? util::math::approx_equal(other.x, start.x)
			&& slope < std::numeric_limits<double>::lowest()
				? other.y >= start.y
				: other.y <= start.y
		: util::math::approx_equal(other.y, other.x * slope - start.x * slope + start.y))
			&& (start.x <= end.x
				? other.x >= start.x
				: other.x <= start.x)
			&& (start.y <= end.y
				? other.y >= start.y
				: other.y <= start.y);
}

util::geom::segment::segment(const util::geom::point& start, const util::geom::point& end)
	: util::geom::line(start, end)
{}

bool util::geom::segment::operator==(const util::geom::segment& other) const {
	return start == other.start && end == other.end || start == other.end && end == other.start;
}

bool util::geom::segment::operator!=(const util::geom::segment& other) const {
	return !operator==(other);
}

double util::geom::segment::length() const {
	return std::hypot(start.x - end.x, start.y - end.y);
}

bool util::geom::segment::contains(const util::geom::point& other) const {
	const double slope = this->slope();
	return (std::isinf(slope)
		? util::math::approx_equal(other.x, start.x)
			&& (other.y >= start.y && other.y <= end.y || other.y <= start.y && other.y >= end.y)
		: util::math::approx_equal(other.y, other.x * slope - start.x * slope + start.y))
			&& (start.x < end.x
				? other.x >= start.x && other.x <= end.x
				: other.x <= start.x && other.x >= end.x)
			&& (start.y < end.y
				? other.y >= start.y && other.y <= end.y
				: other.y <= start.y && other.y >= end.y);
}

util::geom::polygon::polygon(const std::vector<util::geom::point>& points)
	: points(points)
{}

bool util::geom::polygon::operator==(const util::geom::polygon& other) const {
	return util::alg::rotated_match(points.begin(), points.end(), other.points.begin(), other.points.end()) || util::alg::rotated_match(points.rbegin(), points.rend(), other.points.begin(), other.points.end());
}

bool util::geom::polygon::operator!=(const util::geom::polygon& other) const {
	return !operator==(other);
}

double util::geom::polygon::area() const {
	double area = 0;
	for (std::size_t i = 0; i < points.size(); ++i) {
		const util::geom::point& current = points[i];
		const util::geom::point& next = points[(i + 1) % points.size()];
		area += current.x * next.y - next.x * current.y;
	}
	return area / 2;
}

double util::geom::polygon::perimeter() const {
	double perimeter = 0;
	for (std::size_t i = 0; i < points.size(); ++i) {
		const util::geom::point& current = points[i];
		const util::geom::point& next = points[(i + 1) % points.size()];
		perimeter += std::hypot(current.x - next.x, current.y - next.y);
	}
	return perimeter;
}

bool util::geom::polygon::contains(const util::geom::point& point) const {
	util::geom::ray ray(point, { point.x + 1, point.y });
	std::size_t intersections = 0;
	for (std::size_t i = 0; i < points.size(); ++i)
		intersections += ray.intersection(util::geom::segment(points[i], points[(i + 1) % points.size()])).has_value();
	return intersections % 2;
}

util::geom::ellipse::ellipse(const util::geom::point& center, const util::geom::point& radius, const double rotation)
	: center(center), radius(radius), rotation(rotation)
{}

bool util::geom::ellipse::operator==(const util::geom::ellipse& other) const {
	return center == other.center && radius == other.radius && util::math::approx_equal(std::fmod(rotation, std::numbers::pi), std::fmod(other.rotation, std::numbers::pi));
}

bool util::geom::ellipse::operator!=(const util::geom::ellipse& other) const {
	return !operator==(other);
}

double util::geom::ellipse::area() const {
	return std::numbers::pi * radius.x * radius.y;
}

double util::geom::ellipse::perimiter() const {
	return std::numbers::pi * std::sqrt(2 * (radius.x * radius.x + radius.y * radius.y));
}

bool util::geom::ellipse::contains(const util::geom::point& point) const {
	const double a = std::cos(rotation) * (point.x - center.x) + std::sin(rotation) * (point.y - center.y);
	const double b = std::sin(rotation) * (point.x - center.x) - std::cos(rotation) * (point.y - center.y);
	return a * a / radius.x / radius.x + b * b / radius.y / radius.y <= 1;
}
