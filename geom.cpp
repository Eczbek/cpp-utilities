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

util::geom::line::line(const util::geom::point& start, const double angleRadians)
	: start(start)
{
	if (util::math::approx_equal(std::fmod(angleRadians + std::numbers::pi / 2, std::numbers::pi), 0.0))
		end = util::geom::point(start.x, start.y - 1);
	else 
		end = util::geom::point(start.x + 1, std::tan(angleRadians));
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

double util::geom::line::angle_rad() const {
	return std::fmod(std::atan2(start.y - end.y, start.x - end.x) + util::num::tau, std::numbers::pi);
}

double util::geom::line::angle_deg() const {
	return util::math::rad_to_deg(angle_rad());
}

std::optional<util::geom::point> util::geom::line::intersection(const util::geom::line& other) const {
	const double a = start.x - end.x;
	const double b = start.y - end.y;
	const double c = other.start.x - other.end.x;
	const double d = other.start.y - other.end.y;
	const double e = a * d - b * c;
	if (e) {
		const double f = start.x * end.y - start.y * end.x;
		const double g = other.start.x * other.end.y - other.start.y * other.end.x;
		const util::geom::point intersection((c * f - a * g) / e,(d * f - b * g) / e);
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

util::geom::ray::ray(const util::geom::point& start, const double angleRadians)
	: util::geom::line(start, angleRadians)
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

util::geom::rectangle::rectangle(const util::geom::point& corner1, const util::geom::point& corner2)
	: util::geom::polygon({ corner1, { corner2.x, corner1.y }, corner2, { corner1.x, corner2.y } })
{}

bool util::geom::rectangle::operator==(const util::geom::rectangle& other) const {
	return points[0] == other.points[0] && points[2] == other.points[2] || points[0] == other.points[2] && points[2] == other.points[0];
}

bool util::geom::rectangle::operator!=(const util::geom::rectangle& other) const {
	return !operator==(other);
}

double util::geom::rectangle::width() const {
	return std::abs(points[0].x - points[2].x);
}

double util::geom::rectangle::height() const {
	return std::abs(points[0].y - points[2].y);
}

double util::geom::rectangle::area() const {
	return width() * height();
}

double util::geom::rectangle::perimeter() const {
	return 2 * (width() + height());
}

bool util::geom::rectangle::contains(const util::geom::point& other) const {
	return (other.x >= points[0].x && other.x <= points[2].x || other.x <= points[0].x && other.x >= points[2].x)
		&& (other.y >= points[0].y && other.y <= points[2].y || other.y <= points[0].y && other.y >= points[2].y);
}
